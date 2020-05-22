#include "unittest.h"
#include "test_neurons.h"
#include "test_timeframe.h"
#include <stdio.h>

int tests_run = 0;

static char *all_tests() {

  // time frame tests
  mu_run_test(test_timeframe_parameters_given);
  mu_run_test(test_timeframe_ini_given);

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
    printf("%s\n", result);
  } else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}
