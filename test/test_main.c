#include "unittest.h"
#include "test_analytics.h"
#include "test_neurons.h"
#include "test_signals.h"
#include "test_timeframe.h"
#include <stdio.h>

int tests_run = 0;

static char *all_tests() {

  // analytics tests
  mu_run_test(test_firing_rate_lif);

  // time frame tests
  mu_run_test(test_timeframe_parameters_given);
  mu_run_test(test_timeframe_ini_given);
  mu_run_test(test_timeframe_computed_times);

  // signal tests
  mu_run_test(test_bandlimited_white_noise);

  // neuron tests
  mu_run_test(test_neuron_if_parameters);
  mu_run_test(test_neuron_ifac_parameters);
  mu_run_test(test_neuron_pif_ini);
  mu_run_test(test_neuron_lif_ini);

  return 0;
}

int main(int argc, char *argv[]) {
  char *result = all_tests();
  if (result != 0) {
    fprintf(stderr, "TEST FAILED: %s\n", result);
    exit(EXIT_FAILURE);
  } else {
    printf("ALL TESTS PASSED\n");
    printf("Tests run: %d\n", tests_run);
    exit(EXIT_SUCCESS);
  }
}
