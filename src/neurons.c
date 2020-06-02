#include "neurons.h"
#include <math.h>
#include <string.h>

const char *neuron_type_names[] = {"LIF", "PIF", "LIFAC", "PIFAC"};

bool is_ifac(enum NEURON_TYPE  type) {
  if(type == LIFAC || type == PIFAC) {
    return true;
  } else {
    return false;
  }
}

double lif_drift(double v, int i, const if_params_t *params) {
  return params->mu - v;
}

double pif_drift(double v, int i, const if_params_t *params) { return params->mu; }

Neuron *create_neuron_if(double mu, double D, enum NEURON_TYPE type) {

  // define neuron
  Neuron *neuron = malloc(sizeof(Neuron));

  // give if parameters to neuron
  if_params_t *params = malloc(sizeof(if_params_t));
  params->mu = mu;
  params->D = D;
  neuron->if_params = params;
  neuron->adapt_params = NULL;

  // depending on the type, define correct drift
  switch (type) {
  case LIF:
    neuron->type = type;
    neuron->drift = lif_drift;
    break;
  case PIF:
    neuron->type = type;
    neuron->drift = pif_drift;
    break;
  default:
    printf("Invalid IF type\n");
    exit(EXIT_FAILURE);
  }

  return neuron;
}

Neuron *create_neuron_ifac(double mu, double D, double tau_a, double Delta,
                           enum NEURON_TYPE type) {

  // define neuron
  Neuron *neuron = malloc(sizeof(Neuron));

  // give if parameters to neuron
  if_params_t *if_params = malloc(sizeof(if_params_t));
  if_params->mu = mu;
  if_params->D = D;
  neuron->if_params = if_params;

  // give adaptation parameters to neuron
  adapt_params_t *adapt_params = malloc(sizeof(adapt_params_t));
  adapt_params->tau_a = tau_a;
  adapt_params->Delta = Delta;
  neuron->adapt_params = adapt_params;

  // depending on the type, define correct drift
  switch (type) {
  case LIFAC:
    neuron->type = type;
    neuron->drift = lif_drift;
    break;
  case PIFAC:
    neuron->type = type;
    neuron->drift = pif_drift;
    break;
  default:
    printf("Invalid IFAC type\n");
    exit(EXIT_FAILURE);
  }

  return neuron;
}

Neuron *read_neuron_if(ini_t *ini_file) {
  Neuron *neuron = malloc(sizeof(Neuron));

  double mu = NAN, D = NAN;
  const char *if_type = NULL;
  ini_sget(ini_file, "Neuron", "type", NULL, &if_type);
  ini_sget(ini_file, "Neuron", "mu", "%lf", &mu);
  ini_sget(ini_file, "Neuron", "D", "%lf", &D);

  // give if parameters to neuron
  if_params_t *if_params = malloc(sizeof(if_params_t));
  if_params->mu = mu;
  if_params->D = D;
  neuron->if_params = if_params;

  // set adaptation parameters to NULL
  neuron->adapt_params = NULL;

  // depending on the type, define correct drift
  if (strcmp(if_type, "LIF") == 0) {
    neuron->drift = lif_drift;
    neuron->type = LIF;
  } else if (strcmp(if_type, "PIF") == 0) {
    neuron->drift = pif_drift;
    neuron->type = PIF;
  } else {
    printf("Invalid IF type (%s)\n", if_type);
    exit(EXIT_FAILURE);
  }

  return neuron;
}

Neuron *read_neuron_ifac(ini_t *ini_file) {
  Neuron *neuron = malloc(sizeof(Neuron));

  double mu = NAN, D = NAN, tau_a = NAN, Delta = NAN;
  const char *ifac_type = NULL;
  ini_sget(ini_file, "Neuron", "type", NULL, &ifac_type);
  ini_sget(ini_file, "Neuron", "mu", "%lf", &mu);
  ini_sget(ini_file, "Neuron", "D", "%lf", &D);
  ini_sget(ini_file, "Neuron", "tau_a", "%lf", &tau_a);
  ini_sget(ini_file, "Neuron", "Delta", "%lf", &Delta);

  // give if parameters to neuron
  if_params_t *if_params = malloc(sizeof(if_params_t));
  if_params->mu = mu;
  if_params->D = D;
  neuron->if_params = if_params;

  // give adaptation parameters to neuron
  adapt_params_t *adapt_params = malloc(sizeof(adapt_params_t));
  adapt_params->tau_a = tau_a;
  adapt_params->Delta = Delta;
  neuron->adapt_params = adapt_params;

  // depending on the type, define correct drift
  if (strcmp(ifac_type, "LIFAC") == 0) {
    neuron->drift = lif_drift;
    neuron->type = LIF;
  } else if (strcmp(ifac_type, "PIFAC") == 0) {
    neuron->drift = pif_drift;
    neuron->type = PIF;
  } else {
    printf("Invalid IFAC type (%s)\n", ifac_type);
    exit(EXIT_FAILURE);
  }

  return neuron;
}

void free_neuron(Neuron *neuron) {
  if (neuron != NULL) {
    free(neuron->if_params);
    if (neuron->adapt_params != NULL) {
      free(neuron->adapt_params);
    }
    free(neuron);
  }
}

void print_neuron(FILE *stream, const Neuron *neuron) {
  fprintf(stream,
          "# Neuron\n"
          "#\n"
          "# type = %s\n"
          "# mu = %lf\n"
          "# D = %lf\n",
          neuron_type_names[neuron->type], neuron->if_params->mu,
          neuron->if_params->D);

  if (is_ifac(neuron->type)) {
    fprintf(stream,
            "# tau_a = %lf\n"
            "# Delta = %lf\n",
            neuron->adapt_params->tau_a, neuron->adapt_params->Delta);
  }
}

void get_spike_train_if(const gsl_rng *r, const Neuron *neuron,
                        const TimeFrame *time_frame, double *spike_train) {
  double v = 0;
  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += neuron->drift(v, i, neuron->if_params) * dt +
         sqrt(2. * neuron->if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    if (v > 1.0) {
      v = 0.;
      spike_train[i] += 1. / time_frame->dt;
    }
  }
}

void get_spike_train_if_signal(const gsl_rng *r, const Neuron *neuron,
                               const double *signal, const TimeFrame *time_frame,
                               double *spike_train) {

  double v = 0;
  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += (neuron->drift(v, i, neuron->if_params) + signal[i]) * dt +
         sqrt(2. * neuron->if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    if (v > 1.0) {
      v = 0.;
      spike_train[i] += 1. / time_frame->dt;
    }
  }
}

void get_spike_train_ifac(const gsl_rng *r, const Neuron *neuron,
                          const TimeFrame *time_frame, double *spike_train) {

  double v = 0;
  double a = 0;
  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += (neuron->drift(v, i, neuron->if_params) - a) * dt +
         sqrt(2. * neuron->if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    a += -1. / neuron->adapt_params->tau_a * a * dt;
    if (v > 1.0) {
      v = 0.;
      a += neuron->adapt_params->Delta;
      spike_train[i] += 1. / time_frame->dt;
    }
  }
}

void get_spike_train_ifac_signal(const gsl_rng *r, const Neuron *neuron,
                                 const double *signal, const TimeFrame *time_frame,
                                 double *spike_train) {

  double v = 0;
  double a = 0;
  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += (neuron->drift(v, i, neuron->if_params) - a + signal[i]) * dt +
         sqrt(2. * neuron->if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    a += -1. / neuron->adapt_params->tau_a * a * dt;
    if (v > 1.0) {
      v = 0.;
      a += neuron->adapt_params->Delta;
      spike_train[i] += 1. / time_frame->dt;
    }
  }
}
