#include "../src/spike.h"

#include <getopt.h>
#include <stdio.h>
#include <string.h>

void read_cmd(int argc, char *argv[]);

files_t *files;

int main(int argc, char *argv[]) {

  // get input file from the command line
  read_cmd(argc, argv);

  // set logging level
  log_set_level(LOG_INFO);

  // read neuron and time frame from ini file
  log_trace("Read parameters from input file %s", files->input_file);
  ini_t *config = ini_load(files->input_file);
  Neuron *neuron = read_neuron(config);
  TimeFrame *time_frame = read_time_frame(config);

  // setup rng
  gsl_rng_env_setup();
  gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937);

  // define spike train, signal and spike times
  double *spike_train = calloc(time_frame->N, sizeof(double));
  double *signal = malloc((time_frame->N) * sizeof(double));
  double *spike_times = malloc((time_frame->N) * sizeof(double));

  // get a spike train from the neuron
  if (strcmp(neuron_type_names[neuron->type], "LIFAC") == 0 ||
      strcmp(neuron_type_names[neuron->type], "PIFAC") == 0) {
    get_spike_train_ifac(rng, neuron, time_frame, spike_train);
  } else {
    get_spike_train_if(rng, neuron, time_frame, spike_train);
  }

  // calculate stationary firing rate
  double rate = (double)spike_count(time_frame->N, spike_train) /
                (time_frame->t_end - time_frame->t_0);

  // calculate spike times and cv
  int spike_times_length = calculate_isi(time_frame, spike_train, spike_times);
  double cv = calculate_cv(spike_times_length, spike_times);

  printf("# Stationary rate: %lf\n", rate);
  printf("# CV: %lf\n", cv);

  // free memory
  gsl_rng_free(rng);
  free(signal);
  free(spike_train);
  free(spike_times);
  free_neuron(neuron);
  free_time_frame(time_frame);

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
      files = create_files(optarg, "_rate_cv");
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
