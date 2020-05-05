#include "log/log.h"
#include "neurons.h"
#include "signals.h"
#include "statistics.h"
#include "timeframe.h"

#include <complex.h>
#include <fftw3.h>

gsl_rng *rng;

int main(int argc, char *argv[]) {

  log_trace("# SPIKE SUSCEPTIBILITY SIMULATION");
  log_trace("# Defining parameters.");

  // parameters
  const double t_0 = 0.0;
  const double t_end = 500.0;
  const double dt = 1e-2;
  const double T = t_end - t_0;

  // define neuron parameters
  const double mu = 1.1;
  const double D = 1e-3;

  const double c = 0.1;
  const double D_neuron = D * (1.0 - c);

  if_params_t params = {mu, D_neuron};

  const double alpha = D * c;
  const double f_low = 0.;
  const double f_high = 1. / (2. * dt);

  log_trace("# Creating objects.");

  // define time frame and spike train
  TimeFrame *time_frame = create_time_frame(t_0, t_end, dt);


  // define array for susceptibility
  double complex *suscept_lin =
      (double complex *)calloc(time_frame->N / 2 + 1, sizeof(double complex));
  double complex *suscept_nonlin =
     (double complex *)calloc(time_frame->N / 4 + 1, sizeof(double complex));
  //double complex **suscept_nonlin =
  //    calloc(time_frame->N / 4 + 1, sizeof(double complex *));
  //for (int i = 0; i < time_frame->N/4 +1; i ++) {
  //  suscept_nonlin[i] = calloc(time_frame->N/4 + 1, sizeof(double complex));
  //}

  log_trace("# Setting up random number generator.");
  // setup rng
  const gsl_rng_type *type = gsl_rng_mt19937;
  gsl_rng_env_setup();
  rng = gsl_rng_alloc(type);

  log_trace("# Starting calculation.");
  // calculate susceptibility
  const int N_neurons = 1000000;
#pragma omp parallel for
  for (int i = 0; i < N_neurons; i++) {

    // clear spike train and get new signal
    double *spike_train = (double *)calloc(time_frame->N, sizeof(double));

    // define signal and its frequencies
    double *signal = (double *)calloc(time_frame->N, sizeof(double));
    double complex *frequencies =
        (double complex *)calloc(time_frame->N / 2 + 1, sizeof(double complex));

    band_limited_white_noise(rng, alpha, f_low, f_high, time_frame, signal,
                             frequencies);

    // get a spike train from the neuron
    get_spike_train_lif_signal(rng, &params, signal, time_frame, spike_train);

    // calculate susceptibility
    susceptibility_lin_nonlin(frequencies, alpha, spike_train, time_frame,
                              suscept_lin, suscept_nonlin, N_neurons);
    //susceptibility_lin_nonlin_matrix(frequencies, alpha, spike_train, time_frame,
    //                          suscept_lin, suscept_nonlin, N_neurons);

    free(signal);
    free(frequencies);
    free(spike_train);
  }
  log_trace("# Finished calculation.");

  log_trace("# Writing to stdout.");

  // write susceptibility to file
  for (size_t i = 0; i < time_frame->N / 4 + 1; i++) {
    printf("%f,%f,%f,%f,%f\n", (double)i / T, creal(suscept_lin[i]),
           cimag(suscept_lin[i]), creal(suscept_nonlin[i]),
           cimag(suscept_nonlin[i]));
  }

  log_trace("# Freeing memory.");
  // free memory
  free_time_frame(time_frame);
  free(suscept_lin);

  //for (int i = 0; i < time_frame->N/4 +1; i++) {
  //  free(suscept_nonlin[i]);
  //}
  free(suscept_nonlin);

  gsl_rng_free(rng);

  log_trace("# Goodbye.");
  return 0;
}
