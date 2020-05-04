#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>

#include "timeframe.h"
#include "statistics.h"
#include "neurons.h"

void test_spike_train() {
  size_t length = 10;
  spike_train_t *train;
  train = (spike_train_t *) spike_train_alloc(length);

  for (int i = 0; i < train->length; i++) {
    if (i%2 == 0) {
      train->data[i] = true;
    }
    printf("Train[%d] = %s\n", i, train->data[i] ? "true" : "false");
  }

  spike_train_free(train);

  printf("%d\n", train->length);
}

void test_time_frame() {
  double t_0 = 0.0;
  double t_end = 10.0;
  double dt = 1.0;

  time_frame_t *times;
  times = (time_frame_t *) time_frame_alloc(t_0, t_end, dt);

  for (int i = 0; i < times->N; i++) {
    printf("%f\n", times->t[i]);
  }

  time_frame_free(times);
}

void test_spike_times() {
  double t_0 = 0.0;
  double t_end = 10.0;
  double dt = 2.0;

  time_frame_t *time;
  time = (time_frame_t *) time_frame_alloc(t_0, t_end, dt);
  printf("N = %d\n", time->N);

  spike_train_t *train;
  train = (spike_train_t *) spike_train_alloc(time->N);
  train->data[1] = true;
  train->data[4] = true;
  train->data[5] = true;

  double *times;
  times = (double *) malloc(2 * sizeof(double) );

  int length = spike_times(times, train, time);

  for (int i = 0; i < length; i++) {
    printf("%f\n", times[i]);
  }
}

void test_get_spike_train() {

  // setup rng
  const gsl_rng_type *T;
  gsl_rng *r;
  gsl_rng_env_setup();
  T = gsl_rng_default;
  r = gsl_rng_alloc(T);

  time_frame_t *time_frame;
  time_frame = (time_frame_t *) time_frame_alloc(0.0, 10.0, 1e-3);

  spike_train_t *spike_train;
  spike_train = (spike_train_t * ) spike_train_alloc(time_frame->N);

  double *firing_rate;
  firing_rate = (double *) malloc(time_frame->N * sizeof(double));

  if_params_t params;
  params.mu = 2.0;
  params.D = 0.1;

  int count;
  int N = 1e6;
  for (int i = 0; i < N; i++) {
    clear_spike_train(spike_train);
    get_spike_train_pif(r, &params, time_frame, spike_train);
    add_to_firing_rate(firing_rate, N, spike_train, time_frame);
  }

  for(int i = 0; i < time_frame->N; i++){
    printf("%f,%f\n", time_frame->t[i], firing_rate[i]);
  }

}

void test_voronenko() {

  // setup rng
  const gsl_rng_type *T;
  gsl_rng *r;
  gsl_rng_env_setup();
  T = gsl_rng_default;
  r = gsl_rng_alloc(T);

  // define time frame
  time_frame_t *time_frame;
  time_frame = (time_frame_t *) time_frame_alloc(0.0, 100.0, 1e-2);

  // define neuron
  ifac_params_t params;
  params.mu = 1.1;
  params.D = 1e-3;
  params.tau_a = 0.1;
  params.Delta = 3.;

  // define signal
  double *signal;
  signal = (double *) malloc(time_frame->N * sizeof(double));
  for(int i = 0; i < time_frame->N; i++) {
    signal[i] = 0.05*cos(2.0*M_PI*0.215*time_frame->t[i]);
  }

  // allocate memory for spike train
  spike_train_t *spike_train;
  spike_train = (spike_train_t * ) spike_train_alloc(time_frame->N);

  // allocate memory for firing rate
  double *firing_rate;
  firing_rate = (double *) malloc(time_frame->N * sizeof(double));


  int N = 1e5;
  for (int i = 0; i < N; i++) {
    clear_spike_train(spike_train);
    get_spike_train_lifac_signal(r, &params, signal, time_frame, spike_train);
    add_to_firing_rate(firing_rate, N, spike_train, time_frame);
  }

  for (int i = 0; i < time_frame->N; i++) {
    printf("%f,%f\n", time_frame->t[i], firing_rate[i]);
  }

  spike_train_free(spike_train);
  time_frame_free(time_frame);
  free(signal);
  free(firing_rate);

}
