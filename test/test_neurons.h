#include "../src/spike.h"
#include "unittest.h"
#include <stdio.h>

static char *test_neuron_if_parameters() {

  // parameters for the time frame
  const double mu = 12.45;
  const double D = 5.6e-2;

  // create neuron with parameters
  Neuron *pif = create_neuron_if(mu, D, PIF);
  Neuron *lif = create_neuron_if(mu, D, LIF);

  // check if given parameters match the ones in the time frame
  mu_assert("mu in Neuron does not match mu given!", pif->if_params->mu == mu);
  mu_assert("mu in Neuron does not match mu given!", lif->if_params->mu == mu);
  mu_assert("D in Neuron does not match D given!", pif->if_params->D == D);
  mu_assert("D in Neuron does not match D given!", lif->if_params->D == D);
  mu_assert("type in Neuron does not match type given!", pif->type == PIF);
  mu_assert("type in Neuron does not match type given!", lif->type == LIF);

  // free memory
  free_neuron(pif);
  free_neuron(lif);

  return 0;
}

static char *test_neuron_ifac_parameters() {

  // parameters for the time frame
  const double mu = 12.45;
  const double D = 5.6e-2;
  const double tau_a = 0.253;
  const double Delta = 92.2;

  // create neuron with parameters
  Neuron *pifac = create_neuron_ifac(mu, D, tau_a, Delta, PIFAC);
  Neuron *lifac = create_neuron_ifac(mu, D, tau_a, Delta, LIFAC);

  // check if given parameters match the ones in the time frame
  mu_assert("mu in Neuron does not match mu given!", pifac->if_params->mu == mu);
  mu_assert("mu in Neuron does not match mu given!", lifac->if_params->mu == mu);
  mu_assert("D in Neuron does not match D given!", pifac->if_params->D == D);
  mu_assert("D in Neuron does not match D given!", lifac->if_params->D == D);
  mu_assert("tau_a in Neuron does not match tau_a given!",
            pifac->adapt_params->tau_a == tau_a);
  mu_assert("tau_a in Neuron does not match tau_a given!",
            lifac->adapt_params->tau_a == tau_a);
  mu_assert("Delta in Neuron does not match Delta given!",
            pifac->adapt_params->Delta == Delta);
  mu_assert("Delta in Neuron does not match Delta given!",
            lifac->adapt_params->Delta == Delta);
  mu_assert("type in Neuron does not match type given!", pifac->type == PIFAC);
  mu_assert("type in Neuron does not match type given!", lifac->type == LIFAC);

  // free memory
  free_neuron(pifac);
  free_neuron(lifac);

  return 0;
}

static char *test_neuron_pif_ini() {
  ini_t *config = ini_load("../data/testfiles/pif.ini");

  // create neuron with parameters
  Neuron *pif = read_neuron_if(config);

  // check if given parameters match the ones in the time frame
  mu_assert("mu in Neuron does not match mu given!", pif->if_params->mu == 16.53);
  mu_assert("D in Neuron does not match D given!", pif->if_params->D == 44.32);
  mu_assert("type in Neuron does not match type given!", pif->type == PIF);

  print_neuron(stderr, pif);

  // free memory
  free_neuron(pif);

  return 0;
}

static char *test_neuron_lif_ini() {
  ini_t *config = ini_load("../data/testfiles/lif.ini");

  // create neuron with parameters
  Neuron *lif = read_neuron_if(config);

  // check if given parameters match the ones in the time frame
  mu_assert("mu in Neuron does not match mu given!", lif->if_params->mu == 16.53);
  mu_assert("D in Neuron does not match D given!", lif->if_params->D == 44.32);
  mu_assert("type in Neuron does not match type given!", lif->type == LIF);

  print_neuron(stderr, lif);

  // free memory
  free_neuron(lif);

  return 0;
}
