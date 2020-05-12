#include "spike.h"
#include "unittest.h"
#include <stdio.h>

int tests_run = 0;

static char *test_timeframe_parameters_given() {

  // parameters for the time frame
  const double t_0 = 0.0;
  const double t_end = 10.0;
  const double dt = 1.0;

  // create time frame with parameters
  TimeFrame *time_frame = create_time_frame(t_0, t_end, dt);

  // check if given parameters match the ones in the time frame
  mu_assert("t_0 in TimeFrame does not match t_0 given!",
            time_frame->t_0 == t_0);
  mu_assert("t_end in TimeFrame does not match t_end given!",
            time_frame->t_end == t_end);
  mu_assert("dt in TimeFrame does not match dt given!", time_frame->dt == dt);

  // free memory
  free_time_frame(time_frame);

  return 0;
}

static char *test_timeframe_ini_given() {
  ini_t *config = ini_load("../data/testfiles/timeframe.ini");
  TimeFrame *time_frame = read_time_frame(config);

  // check if given parameters match the ones in the time frame
  mu_assert("t_0 in TimeFrame does not match t_0 given!",
            time_frame->t_0 == 1.33);
  mu_assert("t_end in TimeFrame does not match t_end given!",
            time_frame->t_end == 3.56);
  mu_assert("dt in TimeFrame does not match dt given!",
            time_frame->dt == 0.077);

  print_time_frame(stderr, time_frame);

  ini_free(config);
  free_time_frame(time_frame);
  return 0;
}

static char *all_tests() {
  mu_run_test(test_timeframe_parameters_given);
  mu_run_test(test_timeframe_ini_given);
  return 0;
}

int main(int argc, char *argv[]) {
  char *result = all_tests();
  if (result != 0) {
    printf("%s\n", result);
  } else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}
