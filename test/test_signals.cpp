#include "catch.hpp"
#include "statistics.h"
#include "signals.h"

#include <gsl/gsl_rng.h>

TEST_CASE("White noise has standard deviation of 1") {
  // setup rng
  const gsl_rng_type *T;
  gsl_rng *r;
  gsl_rng_env_setup();
  T = gsl_rng_default;
  r = gsl_rng_alloc(T);

  // define time frame
  time_frame_t *time_frame;
  time_frame = (time_frame_t *)time_frame_alloc(0.0, 1000.0, 1e-2);

  // define signal
  double *signal;
  signal = (double *)malloc(time_frame->N * sizeof(double));
  band_limited_white_noise(r, 0.0, 150.0, time_frame, signal);

  REQUIRE( standard_deviation(signal, time_frame->N) == Approx(1.0));
  REQUIRE( mean(signal, time_frame->N) < sqrt((double) 1./(time_frame->N-2)));
}