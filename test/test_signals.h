#ifndef TEST_SIGNALS_H
#define TEST_SIGNALS_H

#include "../src/spike.h"
#include "unittest.h"
#include <stdio.h>

static char *test_bandlimited_white_noise() {

  // define time frame and array for signal
  TimeFrame *time_frame = create_time_frame(0.0, 1000.0, 1e-2);
  double *signal = malloc(time_frame->N * sizeof(double));

  // set up rng
  gsl_rng_env_setup();
  gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937);

  // set parameters for signal
  double alpha = 0.32;
  double f_low = 0.0;
  double f_high = 49.0;

  band_limited_white_noise(rng, alpha, f_low, f_high, time_frame, signal);

  double mean_sig = mean(time_frame->N, signal);
  mu_assert("Mean should be zero", (mean_sig <= 1e-13) && (mean_sig >= 0.0));

  // check that variance lies in some margin
  double margin = 1e-4;
  double var = variance(time_frame->N, signal);
  mu_assert("Variance should be 4*alpha*(f_high-f_low)",
            (var <= 4.0 * alpha * (f_high - f_low) + margin) &&
                (var >= 4.0 * alpha * (f_high - f_low) - margin));

  free_time_frame(time_frame);

  return 0;
}

#endif // TEST_SIGNALS_H
