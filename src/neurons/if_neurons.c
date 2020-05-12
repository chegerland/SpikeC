#include "if_neurons.h"
#include <math.h>
#include <string.h>

const char *if_type_names[] = {"LIF", "PIF"};

double lif_drift(double v, int i, if_params_t *params) {
  return params->mu - v;
}

double pif_drift(double v, int i, if_params_t *params) { return params->mu; }

NeuronIF *create_neuron_if(double mu, double D, enum IF_TYPE type) {

  // define neuron
  NeuronIF *neuron = (NeuronIF *)calloc(1, sizeof(NeuronIF));

  // give parameters to neuron
  if_params_t *params = (if_params_t *)calloc(1, sizeof(if_params_t));
  params->mu = mu;
  params->D = D;
  neuron->params = params;

  // type
  neuron->type = type;

  // depending on the IF type, define correct drift
  switch (neuron->type) {
  case LIF:
    neuron->drift = lif_drift;
    break;
  case PIF:
    neuron->drift = pif_drift;
    break;
  default:
    printf("Unknown neuron type");
    exit(0);
  }

  return neuron;
}

NeuronIF *read_neuron_if(ini_t *ini_file) {
  NeuronIF *neuron = (NeuronIF *)calloc(1, sizeof(NeuronIF));

  double mu = NAN, D = NAN;
  const char *if_type = NULL;
  ini_sget(ini_file, "Neuron", "type", NULL, &if_type);
  ini_sget(ini_file, "Neuron", "mu", "%lf", &mu);
  ini_sget(ini_file, "Neuron", "D", "%lf", &D);

  // give parameters to neuron
  if_params_t *params = (if_params_t *)calloc(1, sizeof(if_params_t));
  params->mu = mu;
  params->D = D;
  neuron->params = params;

  if (strcmp(if_type, "LIF") == 0) {
    neuron->drift = lif_drift;
    neuron->type = LIF;
  } else if (strcmp(if_type, "PIF") == 0) {
    neuron->drift = pif_drift;
    neuron->type = PIF;
  } else {
    printf("Unknown neuron type");
    exit(0);
  }

  return neuron;
}

void free_neuron_if(NeuronIF *neuron) {
  if (neuron != NULL) {
    free(neuron->params);
    free(neuron);
  }
}

void print_neuron_if(FILE *fp, NeuronIF *neuron) {
  fprintf(fp,
          "# Neuron\n"
          "#\n"
          "# type = %s\n"
          "# mu = %lf\n"
          "# D = %lf\n",
          if_type_names[neuron->type], neuron->params->mu, neuron->params->D);
}

void get_spike_train_if(const gsl_rng *r, NeuronIF *neuron,
                        TimeFrame *time_frame, double *spike_train) {

  double v = 0;
  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += neuron->drift(v, i, neuron->params) * dt +
         sqrt(2. * neuron->params->D) * gsl_ran_gaussian(r, sqrt(dt));
    if (v > 1.0) {
      v = 0.;
      spike_train[i] += 1. / time_frame->dt;
    }
  }
}

void get_spike_train_if_signal(const gsl_rng *r, NeuronIF *neuron,
                               const double *signal, TimeFrame *time_frame,
                               double *spike_train) {

  double v = 0;
  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += (neuron->drift(v, i, neuron->params) + signal[i]) * dt +
         sqrt(2. * neuron->params->D) * gsl_ran_gaussian(r, sqrt(dt));
    if (v > 1.0) {
      v = 0.;
      spike_train[i] += 1. / time_frame->dt;
    }
  }
}
