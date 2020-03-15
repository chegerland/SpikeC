#include "catch.hpp"
#include "timeframe.h"

TEST_CASE("Time frame allocation works correctly") {
  // define parameters
  double t_0 = 0.0;
  double t_end = 13.0;
  double dt = 1e-2;

  // allocate time frame
  time_frame_t *time_frame;
  time_frame = time_frame_alloc(t_0, t_end, dt);

  // check if parameters are set correctly
  REQUIRE(time_frame->t_0 == t_0);
  REQUIRE(time_frame->t_end == t_end);
  REQUIRE(time_frame->dt == dt);
  REQUIRE(time_frame->N == (int)((t_end - t_0) / dt));

  time_frame_free(time_frame);
}

TEST_CASE("Time frame times are calculated correctly") {
  // define parameters
  double t_0 = 1.0;
  double t_end = 10.0;
  double dt = 1.;

  // allocate time frame
  time_frame_t *time_frame;
  time_frame = time_frame_alloc(t_0, t_end, dt);

  // times should be 1, 2, ...
  for (unsigned int i = 0; i < time_frame->N; i++) {
    REQUIRE(time_frame->t[i] == (double) i+1);
  }
}
