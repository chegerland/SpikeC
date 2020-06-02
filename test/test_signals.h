#ifndef TEST_SIGNALS_H
#define TEST_SIGNALS_H

#include "../src/spike.h"
#include "unittest.h"
#include <stdio.h>

static char *test_bandlimited_white_noise() {

  TimeFrame *time_frame = create_time_frame(0.0, 1000.0, 1e-2);
  double *signal = malloc(time_frame->N * sizeof(double));

  gsl_rng_env_setup();
  gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937);

  double alpha = 0.32;
  double f_low = 0.0;
  double f_high = 49.0;

  band_limited_white_noise(rng, alpha, f_low, f_high, time_frame, signal);

  double var = variance(time_frame->N, signal);

  printf("Variance(ist): %lf\n", var);
  printf("Variance(soll): %lf\n", 4.0*alpha*(f_high - f_low));

  printf("%lf\n", time_frame->t[0]);
  printf("%lf\n", time_frame->t[time_frame->N-1]);

  free_time_frame(time_frame);

  return 0;
}

#endif // TEST_SIGNALS_H
