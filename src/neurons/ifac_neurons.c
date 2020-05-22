#include "ifac_neurons.h"
#include <math.h>

NeuronIFAC *create_neuron_ifac(double mu, double D, double tau_a, double Delta,
                         enum IFAC_TYPE type) {

  // define neuron
  NeuronIFAC *neuron = (NeuronIFAC *)calloc(1, sizeof(NeuronIFAC));

  // give parameters to neuron
  if_params_t *params = (if_params_t *)calloc(1, sizeof(if_params_t));
  params->mu = mu;
  params->D = D;
  neuron->params = params;
  adapt_params_t *adapt_params =
      (adapt_params_t *)calloc(1, sizeof(adapt_params_t));
  adapt_params->tau_a = tau_a;
  adapt_params->Delta = Delta;
  neuron->adapt_params = adapt_params;
  neuron->type = type;

  // depending on the IFAC type, define correct drift
  switch (type) {
  case LIFAC:
    neuron->drift = lif_drift;
    break;
  case PIFAC:
    neuron->drift = pif_drift;
    break;
  default:
    printf("Unknown neuron type");
    exit(0);
  }

  return neuron;
}

void free_neuron_ifac(NeuronIFAC *neuron) {
  if (neuron != NULL) {
    free(neuron->params);
    free(neuron->adapt_params);
    free(neuron);
  }
}

void get_spike_train_ifac(const gsl_rng *r, NeuronIFAC *neuron,
                          TimeFrame *time_frame, double *spike_train) {

  double v = 0;
  double a = 0;
  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += (neuron->drift(v, i, neuron->params) - a) * dt +
         sqrt(2. * neuron->params->D) * gsl_ran_gaussian(r, sqrt(dt));
    a += -1. / neuron->adapt_params->tau_a * a * dt;
    if (v > 1.0) {
      v = 0.;
      a += neuron->adapt_params->Delta;
      spike_train[i] += 1. / time_frame->dt;
    }
  }
}

void get_spike_train_ifac_signal(const gsl_rng *r, NeuronIFAC *neuron,
                                 const double *signal, TimeFrame *time_frame,
                                 double *spike_train) {

  double v = 0;
  double a = 0;
  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += (neuron->drift(v, i, neuron->params) - a + signal[i]) * dt +
         sqrt(2. * neuron->params->D) * gsl_ran_gaussian(r, sqrt(dt));
    a += -1. / neuron->adapt_params->tau_a * a * dt;
    if (v > 1.0) {
      v = 0.;
      a += neuron->adapt_params->Delta;
      spike_train[i] += 1. / time_frame->dt;
    }
  }
}
