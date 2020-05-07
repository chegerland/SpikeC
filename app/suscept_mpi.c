#include "log/log.h"
#include "neurons/if_neurons.h"
#include "signals.h"
#include "statistics.h"
#include "timeframe.h"

#include <complex.h>
#include <mpi.h>
#include <stdio.h>

void master();
void minion();

// define parameters
const double t_0 = 0.0;
const double t_end = 700.0;
const double dt = 5e-3;
const double T = t_end - t_0;

const double mu = 1.1;
const double D = 1e-3;

const double c = 0.8;
const double D_neuron = D * (1.0 - c);
enum IF_TYPE neuron_type = LIF;
if_params_t params = {mu, D_neuron};

const double alpha = D * c;
const double f_low = 0.;
const double f_high = 1. / (2. * dt);

const int N_neurons = (int)1e5;

int main(int argc, char *argv[]) {

  // initialize mpi
  MPI_Init(&argc, &argv);

  // get world rank and size
  int world_rank = 0;
  int world_size = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  if (world_rank == 0)
    master();
  else
    minion();

  // finalize mpi
  MPI_Finalize();

  return 0;
}

void master() {
  log_trace("# SPIKE SUSCEPTIBILITY SIMULATION");

  // get world size
  int world_size = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int trials = (int) N_neurons / world_size;

  log_trace("# Sending %d trials to %d processes.", trials, world_size - 1);
  // send number of trials to each process
  for (int i = 1; i < world_size; i++) {
    MPI_Send(&trials, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
  }

  log_trace("# Creating objects.");
  // define time frame
  TimeFrame *time_frame = create_time_frame(t_0, t_end, dt);
  NeuronIF *neuron = create_neuron_if(mu, D, neuron_type);

  // define array for susceptibility
  double complex *suscept_lin =
      (double complex *)calloc(time_frame->N / 2 + 1, sizeof(double complex));
  double complex *suscept_nonlin =
      (double complex *)calloc(time_frame->N / 4 + 1, sizeof(double complex));

  // setup rng with world rank
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  log_trace("# Setting up rng with seed %d.", world_rank);
  gsl_rng *rng = NULL;
  const gsl_rng_type *type = gsl_rng_mt19937;
  gsl_rng_env_setup();
  rng = gsl_rng_alloc(type);
  gsl_rng_set(rng, world_rank);

  log_trace("# Calculating %d trials.", trials);
  // calculate susceptibility
  for (int i = 0; i < trials; i++) {

    // define spike train
    double *spike_train = (double *)calloc(time_frame->N, sizeof(double));

    // define signal and its frequencies
    double *signal = (double *)calloc(time_frame->N, sizeof(double));
    double complex *frequencies =
        (double complex *)calloc(time_frame->N / 2 + 1, sizeof(double complex));

    // generate new white noise signal
    band_limited_white_noise(rng, alpha, f_low, f_high, time_frame, signal,
                             frequencies);

    // get a spike train from the neuron
    get_spike_train_if_signal(rng, neuron, signal, time_frame, spike_train);

    // calculate susceptibility
    susceptibility_lin_nonlin(frequencies, alpha, spike_train, time_frame,
                              suscept_lin, suscept_nonlin, N_neurons);

    free(signal);
    free(frequencies);
    free(spike_train);
  }
  log_trace("# Finished calculation.");

  log_trace("# Receiving values from subprocesses.");
  // define array for susceptibility
  double complex *tmp_suscept_lin =
      (double complex *)calloc(time_frame->N / 2 + 1, sizeof(double complex));
  double complex *tmp_suscept_nonlin =
      (double complex *)calloc(time_frame->N / 4 + 1, sizeof(double complex));

  // receive arrays back from subprocesses
  MPI_Status status;
  for (int i = 1; i < world_size; i++) {

    // receive arrays
    MPI_Recv(tmp_suscept_lin, time_frame->N / 2 + 1, MPI_C_DOUBLE_COMPLEX,
             MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(tmp_suscept_nonlin, time_frame->N / 4 + 1, MPI_C_DOUBLE_COMPLEX,
             MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);

    // add array to overall susceptibilities
    for (int j = 0; j < time_frame->N / 4 + 1; j++) {
      suscept_lin[j] += tmp_suscept_lin[j];
      suscept_nonlin[j] += tmp_suscept_nonlin[j];
    }
  }
  log_trace("# Received all values from subprocesses.");

  // free memory of temporary susceptibility
  free(tmp_suscept_lin);
  free(tmp_suscept_nonlin);

  // write to file
  log_trace("# Writing results to file.");
  FILE *f;
  f = fopen("suscepts_N_1e5_mpi.csv", "w");

  for (size_t i = 0; i < time_frame->N / 4 + 1; i++) {
    fprintf(f, "%f,%f,%f,%f,%f\n", (double)i / T, creal(suscept_lin[i]),
            cimag(suscept_lin[i]), creal(suscept_nonlin[i]),
            cimag(suscept_nonlin[i]));
  }
  fclose(f);

  log_trace("# Freeing memory.");
  // free memory
  free(suscept_lin);
  free(suscept_nonlin);
  free(time_frame);
  free_neuron_if(neuron);
  gsl_rng_free(rng);

  log_trace("# Goodbye.");
}

void minion() {

  // receive trials from master
  int trials = 0;
  MPI_Status status;
  MPI_Recv(&trials, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

  // define time frame
  TimeFrame *time_frame = create_time_frame(t_0, t_end, dt);
  NeuronIF *neuron = create_neuron_if(mu, D, neuron_type);


  // define array for susceptibility
  double complex *suscept_lin =
      (double complex *)calloc(time_frame->N / 2 + 1, sizeof(double complex));
  double complex *suscept_nonlin =
      (double complex *)calloc(time_frame->N / 4 + 1, sizeof(double complex));

  // setup rng with world rank
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  gsl_rng *rng = NULL;
  const gsl_rng_type *type = gsl_rng_mt19937;
  gsl_rng_env_setup();
  rng = gsl_rng_alloc(type);
  gsl_rng_set(rng, world_rank);

  // calculate susceptibility
  for (int i = 0; i < trials; i++) {

    // define spike train
    double *spike_train = (double *)calloc(time_frame->N, sizeof(double));

    // define signal and its frequencies
    double *signal = (double *)calloc(time_frame->N, sizeof(double));
    double complex *frequencies =
        (double complex *)calloc(time_frame->N / 2 + 1, sizeof(double complex));

    // generate new white noise signal
    band_limited_white_noise(rng, alpha, f_low, f_high, time_frame, signal,
                             frequencies);

    // get a spike train from the neuron
    get_spike_train_if_signal(rng, neuron, signal, time_frame, spike_train);

    // calculate susceptibilities
    susceptibility_lin_nonlin(frequencies, alpha, spike_train, time_frame,
                              suscept_lin, suscept_nonlin, N_neurons);

    free(signal);
    free(frequencies);
    free(spike_train);
  }

  // send arrays to master
  MPI_Send(suscept_lin, time_frame->N / 2 + 1, MPI_C_DOUBLE_COMPLEX, 0, 1,
           MPI_COMM_WORLD);
  MPI_Send(suscept_nonlin, time_frame->N / 4 + 1, MPI_C_DOUBLE_COMPLEX, 0, 2,
           MPI_COMM_WORLD);

  // free memory
  free(suscept_lin);
  free(time_frame);
  free(suscept_nonlin);
  free_neuron_if(neuron);
  gsl_rng_free(rng);
}
