#include "../src/timeframe.h"
#include <gsl/gsl_rng.h>
#include "signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

gsl_rng *rng;

int main(int argc, char *argv[]) {

  // parameters
  const double t_0 = 0.0;
  const double t_end = 500.0;
  const double dt = 1e-2;
  //double T = t_end - t_0;

  const double alpha = 0.35;
  const double f_low = 0.;
  const double f_high = 1. / (2. * dt);

  // define time frame and spike train
  TimeFrame *time_frame = create_time_frame(t_0, t_end, dt);

  // setup rng
  const gsl_rng_type *type = gsl_rng_mt19937;
  gsl_rng_env_setup();
  rng = gsl_rng_alloc(type);

  // define signal and its frequencies
  double *signal = (double *)calloc(time_frame->N, sizeof(double));
  double complex *frequencies =
      (double complex *)calloc(time_frame->N / 2 + 1, sizeof(double complex));

  band_limited_white_noise(rng, alpha, f_low, f_high, time_frame, signal,
                           frequencies);

  printf("Power spectrum = %f\n", pow(cabs(frequencies[3]),2));

  // free memory
  free_time_frame(time_frame);
  free(signal);
  free(frequencies);
  gsl_rng_free(rng);

  return 0;
}
