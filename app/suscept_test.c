#include "neurons.h"
#include "signals.h"
#include "spiketrain.h"
#include "statistics.h"
#include "timeframe.h"

int main(int argc, char *argv[]) {
  // setup rng
  const gsl_rng_type *T;
  gsl_rng *r;
  gsl_rng_env_setup();
  T = gsl_rng_default;
  r = gsl_rng_alloc(T);

  // define time frame
  time_frame_t *time_frame;
  time_frame = (time_frame_t *)time_frame_alloc(0.0, 200.0, 1e-2);

  // define neuron
  ifac_params_t params;
  params.mu = 3.5;
  params.D = 1e-1;
  params.tau_a = 10;
  params.Delta = 0.3;

  // define signal
  double *signal;
  signal = (double *)malloc(time_frame->N * sizeof(double));
  //cosine_signal(0.05, 0.215, time_frame, signal);
  band_limited_white_noise(r, 0.05, 0.0, 100.0, time_frame, signal);

  // allocate memory for spike train
  spike_train_t *spike_train;
  spike_train = (spike_train_t *)spike_train_alloc(time_frame->N);

  // allocate memory for firing rate
  double *firing_rate;
  firing_rate = (double *)malloc(time_frame->N * sizeof(double));
  for (int i = 0; i < time_frame->N; i++) {
    firing_rate[i] = 0.0;
  }

  int N_sig = 10;
  for (int j = 0; j < N_sig; j++) {
    // generate white noise
    band_limited_white_noise(r, 0.05, 0.0, 100.0, time_frame, signal);

    //get firing rate
    int N = 1e4;
    for (int i = 0; i < N; i++) {
      clear_spike_train(spike_train);
      get_spike_train_lifac_signal(r, &params, signal, time_frame, spike_train);
      add_to_firing_rate(firing_rate, N, spike_train, time_frame);
    }

  }

  for (int i = 0; i < time_frame->N; i++) {
    printf("%f,%f,%f\n", time_frame->t[i], firing_rate[i], signal[i]);
  }

  spike_train_free(spike_train);
  time_frame_free(time_frame);
  free(signal);
  free(firing_rate);
  return 0;
}
