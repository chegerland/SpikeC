#include "spike.h"
#include "unittest.h"
#include <stdio.h>

int tests_run = 0;

static char *test_neuron_if_parameters() {

  // parameters for the time frame
  const double mu = 12.45;
  const double D = 5.6e-2;

  // create neuron with parameters
  NeuronIF *pif = create_neuron_if(mu, D, PIF);
  NeuronIF *lif = create_neuron_if(mu, D, LIF);

  // check if given parameters match the ones in the time frame
  mu_assert("mu in Neuron does not match mu given!", pif->params->mu == mu);
  mu_assert("mu in Neuron does not match mu given!", lif->params->mu == mu);
  mu_assert("D in Neuron does not match D given!", pif->params->D == D);
  mu_assert("D in Neuron does not match D given!", lif->params->D == D);
  mu_assert("type in Neuron does not match type given!", pif->type == PIF);
  mu_assert("type in Neuron does not match type given!", lif->type == LIF);

  // free memory
  free_neuron_if(pif);
  free_neuron_if(lif);

  return 0;
}

static char *test_neuron_pif_ini() {
  ini_t *config = ini_load("../data/testfiles/pif.ini");

  // create neuron with parameters
  NeuronIF *pif = read_neuron_if(config);

  // check if given parameters match the ones in the time frame
  mu_assert("mu in Neuron does not match mu given!", pif->params->mu == 16.53);
  mu_assert("D in Neuron does not match D given!", pif->params->D == 44.32);
  mu_assert("type in Neuron does not match type given!", pif->type == PIF);

  print_neuron_if(stderr, pif);

  // free memory
  free_neuron_if(pif);

  return 0;
}

static char *test_neuron_lif_ini() {
  ini_t *config = ini_load("../data/testfiles/lif.ini");

  // create neuron with parameters
  NeuronIF *lif = read_neuron_if(config);

  // check if given parameters match the ones in the time frame
  mu_assert("mu in Neuron does not match mu given!", lif->params->mu == 16.53);
  mu_assert("D in Neuron does not match D given!", lif->params->D == 44.32);
  mu_assert("type in Neuron does not match type given!", lif->type == LIF);

  print_neuron_if(stderr, lif);

  // free memory
  free_neuron_if(lif);

  return 0;
}

static char *all_tests() {
  mu_run_test(test_neuron_if_parameters);
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
