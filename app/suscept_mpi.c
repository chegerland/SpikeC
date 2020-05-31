#include "../src/spike.h"

#include <complex.h>
#include <getopt.h>
#include <mpi.h>
#include <stdio.h>

void read_cmd(int argc, char *argv[]);
void master(suscept_sim_t *suscept_sim, int world_rank);
void minion(suscept_sim_t *suscept_sim, int world_rank);
void calculate_susceptibility(suscept_sim_t *suscept_sim, int trials,
                              int world_rank);
void receive_arrays_from_minions(suscept_sim_t *suscept_sim, int world_size);

files_t *files;

int main(int argc, char *argv[]) {

  // get input file from the command line
  read_cmd(argc, argv);

  // set logging level
  log_set_level(LOG_INFO);

  // define susceptbility simulation
  log_trace("Read parameters from input file %s", files->input_file);
  ini_t *config = ini_load(files->input_file);
  suscept_sim_t *suscept_sim = read_suscept_sim(config);

  // initialize mpi
  MPI_Init(&argc, &argv);

  // get world rank and size
  int world_rank = 0, world_size = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // depending on world rank, process is either master or minion
  if (world_rank == 0)
    master(suscept_sim, world_rank);
  else
    minion(suscept_sim, world_rank);

  // finalize mpi
  MPI_Finalize();

  // free memory
  log_trace("Freeing memory.");
  ini_free(config);
  free_suscept_sim(suscept_sim);

  return 0;
}

void read_cmd(int argc, char *argv[]) {

  while (1) {
    static struct option long_options[] = {{"file", required_argument, 0, 'f'},
                                           {0, 0, 0, 0}};
    /* getopt_long stores the option index here. */
    int option_index = 0;

    int c = getopt_long(argc, argv, "f:", long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1)
      break;

    switch (c) {
    case 0:
      /* If this option set a flag, do nothing else now. */
      if (long_options[option_index].flag != 0)
        break;
      printf("option %s", long_options[option_index].name);
      if (optarg)
        printf(" with arg %s", optarg);
      printf("\n");
      break;

    case 'f':
      files = create_files(optarg);
      break;

    case '?':
      /* getopt_long already printed an error message. */
      break;

    default:
      abort();
    }
  }

  /* Print any remaining command line arguments (not options). */
  if (optind < argc) {
    printf("non-option ARGV-elements: ");
    while (optind < argc)
      printf("%s ", argv[optind++]);
    putchar('\n');
  }
}

void master(suscept_sim_t *suscept_sim, int world_rank) {

  // get world size
  int world_size = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // calculate number of trials for each subprocess
  int trials = (int)suscept_sim->N_neurons / world_size;

  // send number of trials to each process
  log_info("Sending %d trials to %d processes.", trials, world_size - 1);
  for (int i = 1; i < world_size; i++) {
    MPI_Send(&trials, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
  }

  // calculate the susceptibility
  calculate_susceptibility(suscept_sim, trials, world_rank);

  receive_arrays_from_minions(suscept_sim, world_size);

  // write to file
  log_info("Writing results to output file %s.", files->output_file);
  FILE *f = NULL;
  f = fopen(files->output_file, "w");

  print_suscept_sim(f, suscept_sim);
  write_suscepts_to_file(f, suscept_sim);

  fclose(f);

  log_info("Goodbye.");
}

void receive_arrays_from_minions(suscept_sim_t *suscept_sim, int world_size) {
  // better readibility
  double complex *suscept_lin = suscept_sim->suscept_lin;
  double complex *suscept_nonlin = suscept_sim->suscept_nonlin;
  TimeFrame *time_frame = suscept_sim->time_frame;

  // define array for susceptibility
  double complex *tmp_suscept_lin =
      (double complex *)calloc(time_frame->N / 2 + 1, sizeof(double complex));
  double complex *tmp_suscept_nonlin =
      (double complex *)calloc(time_frame->N / 4 + 1, sizeof(double complex));

  // receive arrays back from subprocesses
  MPI_Status status;
  log_info("Receiving values from subprocesses.");
  for (int i = 1; i < world_size; i++) {

    // receive arrays
    MPI_Recv(tmp_suscept_lin, (int)time_frame->N / 2 + 1, MPI_C_DOUBLE_COMPLEX,
             MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(tmp_suscept_nonlin, (int)time_frame->N / 4 + 1,
             MPI_C_DOUBLE_COMPLEX, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);

    // add array to overall susceptibilities
    for (int j = 0; j < time_frame->N / 4 + 1; j++) {
      suscept_lin[j] += tmp_suscept_lin[j];
      suscept_nonlin[j] += tmp_suscept_nonlin[j];
    }
  }
  log_info("Received all values from subprocesses.");

  // free memory of temporary susceptibility
  free(tmp_suscept_lin);
  free(tmp_suscept_nonlin);
}

void minion(suscept_sim_t *suscept_sim, int world_rank) {

  // receive number of trials from master
  int trials = 0;
  MPI_Status status;
  MPI_Recv(&trials, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

  // define objects
  TimeFrame *time_frame = suscept_sim->time_frame;

  // define array for susceptibility
  double complex *suscept_lin = suscept_sim->suscept_lin;
  double complex *suscept_nonlin = suscept_sim->suscept_nonlin;

  calculate_susceptibility(suscept_sim, trials, world_rank);

  // send arrays to master
  log_trace("Sending data back to master.");
  MPI_Send(suscept_lin, (int)time_frame->N / 2 + 1, MPI_C_DOUBLE_COMPLEX, 0, 1,
           MPI_COMM_WORLD);
  MPI_Send(suscept_nonlin, (int)time_frame->N / 4 + 1, MPI_C_DOUBLE_COMPLEX, 0,
           2, MPI_COMM_WORLD);
}

void calculate_susceptibility(suscept_sim_t *suscept_sim, int trials,
                              int world_rank) {

  // for better readibility
  TimeFrame *time_frame = suscept_sim->time_frame;
  Neuron *neuron = suscept_sim->neuron;
  double complex *suscept_lin = suscept_sim->suscept_lin;
  double complex *suscept_nonlin = suscept_sim->suscept_nonlin;

  // setup rng with world rank
  log_trace("Setting up rng with seed %d.", world_rank);
  gsl_rng_env_setup();
  gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(rng, world_rank);

  log_trace("Calculating %d trials.", trials);
  // calculate susceptibility
  for (int i = 0; i < trials; i++) {

    // define spike train
    double *spike_train = (double *)calloc(time_frame->N, sizeof(double));

    // define signal and its frequencies
    double *signal = (double *)calloc(time_frame->N, sizeof(double));

    // generate new white noise signal
    band_limited_white_noise(rng, suscept_sim->alpha, 0.,
                             1. / (2. * time_frame->dt), time_frame, signal);

    // get a spike train from the neuron
    suscept_sim->get_spike_train(rng, neuron, signal, time_frame, spike_train);

    // calculate susceptibility
    susceptibility_lin_nonlin(signal, spike_train, time_frame, suscept_lin,
                              suscept_nonlin, suscept_sim->N_neurons);

    free(signal);
    free(spike_train);
  }
  log_trace("# Finished calculation.");

  // free rng
  gsl_rng_free(rng);
}
