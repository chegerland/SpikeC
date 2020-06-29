#include "neurons.h"
#include <math.h>
#include <string.h>

// all neuron types as strings
const char *neuron_type_names[] = {"LIF", "PIF", "LIFAC", "PIFAC"};

// checks if a given neuron type is an IFAC
bool is_ifac(enum NEURON_TYPE type) {
  if (type == LIFAC || type == PIFAC) {
    return true;
  } else {
    return false;
  }
}

// drift for leaky integrate-and-fire neuron
double lif_drift(double v, const if_params_t *params) {
  return params->mu - v;
}

// drift for perfect integrate-and-fire neuron
double pif_drift(double v, const if_params_t *params) {
  return params->mu;
}

// creates an if neuron from parameters
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

// creates an ifac neuron from parameters
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

// creates a neuron from ini file
Neuron *read_neuron(ini_t *ini_file) {
  Neuron *neuron = malloc(sizeof(Neuron));

  double mu, D;
  const char *type = NULL;
  ini_sget(ini_file, "Neuron", "type", NULL, &type);
  ini_sget(ini_file, "Neuron", "mu", "%lf", &mu);
  ini_sget(ini_file, "Neuron", "D", "%lf", &D);

  // give if parameters to neuron
  if_params_t *if_params = malloc(sizeof(if_params_t));
  if_params->mu = mu;
  if_params->D = D;
  neuron->if_params = if_params;

  // give adaptation parameters to neuron
  adapt_params_t *adapt_params = NULL;

  // if neuron is ifac define adaptation parameters
  if (strcmp(type, "LIFAC") == 0 || strcmp(type, "PIFAC") == 0) {

    // read adaptation parameters
    double tau_a, Delta;
    ini_sget(ini_file, "Neuron", "tau_a", "%lf", &tau_a);
    ini_sget(ini_file, "Neuron", "Delta", "%lf", &Delta);

    // define adaptation parameters
    adapt_params = malloc(sizeof(adapt_params_t));
    adapt_params->tau_a = tau_a;
    adapt_params->Delta = Delta;

    neuron->adapt_params = adapt_params;
  }

  // depending on the type, define correct drift
  if (strcmp(type, "LIF") == 0) {
    neuron->drift = lif_drift;
    neuron->type = LIF;
  } else if (strcmp(type, "PIF") == 0) {
    neuron->drift = pif_drift;
    neuron->type = PIF;
  } else if (strcmp(type, "LIFAC") == 0) {
    neuron->drift = lif_drift;
    neuron->type = LIFAC;
  } else if (strcmp(type, "PIFAC") == 0) {
    neuron->drift = pif_drift;
    neuron->type = PIFAC;
  } else {
    printf("Invalid Neuron type (%s)\n", type);
    exit(EXIT_FAILURE);
  }

  return neuron;
}

// free memory associated with neuron
void free_neuron(Neuron *neuron) {
  if (neuron != NULL) {
    free(neuron);
  }
}

// print information of neuron to stream
void print_neuron(FILE *stream, const Neuron *neuron) {
  fprintf(stream,
          "# [Neuron]\n"
          "# type = %s\n"
          "# mu = %lf\n"
          "# D = %lf\n",
          neuron_type_names[neuron->type], neuron->if_params->mu,
          neuron->if_params->D);

  if (neuron->adapt_params != NULL) {
    fprintf(stream,
            "# tau_a = %lf\n"
            "# Delta = %lf\n",
            neuron->adapt_params->tau_a, neuron->adapt_params->Delta);
  }
}

/*
 * get spike train of an if neuron
 * Uses Euler-Maruyama algorithm with the usual fire-and-reset condition.
 * At the spike we add (!) 1/dt to the appropriate spike train entry.
 */
void get_spike_train_if(const gsl_rng *r, const Neuron *neuron,
                        const SpikeTrain *spike_train) {
  double v = 0.;
  const double dt = spike_train->dt;

  for (size_t i = 0; i < spike_train->length; i++) {
    v += neuron->drift(v, neuron->if_params) * dt +
         sqrt(2. * neuron->if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    if (v > 1.0) {
      v = 0.;
      spike_train->spike_array[i] += 1. / spike_train->dt;
    }
  }
}

/*
 * Get spike train of an if neuron with applied signal.
 * Uses Euler-Maruyama algorithm with the usual fire-and-reset condition.
 * At the spike we add (!) 1/dt to the appropriate spike train entry.
 */
void get_spike_train_if_signal(const gsl_rng *r, const Neuron *neuron,
                               const double *signal,
                               const SpikeTrain *spike_train) {

  double v = 0;
  const double dt = spike_train->dt;

  for (size_t i = 0; i < spike_train->length; i++) {
    v += (neuron->drift(v, neuron->if_params) + signal[i]) * dt +
         sqrt(2. * neuron->if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    if (v > 1.0) {
      v = 0.;
      spike_train->spike_array[i] += 1. / spike_train->dt;
    }
  }
}

/*
 * get spike train of an ifac neuron
 * Uses Euler-Maruyama algorithm with the usual fire-and-reset condition.
 * At the spike we add (!) 1/dt to the appropriate spike train entry.
 */
void get_spike_train_ifac(const gsl_rng *r, const Neuron *neuron,
                          const SpikeTrain *spike_train) {

  double v = 0;
  double a = 0;
  const double dt = spike_train->dt;

  for (size_t i = 0; i < spike_train->length; i++) {
    v += (neuron->drift(v, neuron->if_params) - a) * dt +
         sqrt(2. * neuron->if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    a += -1. / neuron->adapt_params->tau_a * a * dt;
    if (v > 1.0) {
      v = 0.;
      a += neuron->adapt_params->Delta;
      spike_train->spike_array[i] += 1. / spike_train->dt;
    }
  }
}

/*
 * get spike train of an ifac neuron with applied signal
 * Uses Euler-Maruyama algorithm with the usual fire-and-reset condition.
 * At the spike we add (!) 1/dt to the appropriate spike train entry.
 */
void get_spike_train_ifac_signal(const gsl_rng *r, const Neuron *neuron,
                                 const double *signal,
                                 const SpikeTrain *spike_train) {

  double v = 0;
  double a = 0;
  const double dt = spike_train->dt;

  for (size_t i = 0; i < spike_train->length; i++) {
    v += (neuron->drift(v, neuron->if_params) - a + signal[i]) * dt +
         sqrt(2. * neuron->if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    a += -1. / neuron->adapt_params->tau_a * a * dt;
    if (v > 1.0) {
      v = 0.;
      a += neuron->adapt_params->Delta;
      spike_train->spike_array[i] += 1. / spike_train->dt;
    }
  }
}

/*
 * get the trajectory of an if neuron
 * Uses Euler-Maruyama algorithm with the usual fire-and-reset condition.
 */
void get_trajectory_if(const gsl_rng *r, const Neuron *neuron,
                       const TimeFrame *time_frame, double *v) {
  v[0] = 0;
  const double dt = time_frame->dt;

  for (size_t i = 0; i < time_frame->N; i++) {
    v[i + 1] = v[i] + neuron->drift(v[i], neuron->if_params) * dt +
               sqrt(2. * neuron->if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    if (v[i + 1] > 1.0) {
      v[i + 1] = 0.;
    }
  }
}

/*
 * get trajectory of an if neuron with applied signal
 * Uses Euler-Maruyama algorithm with the usual fire-and-reset condition.
 */
void get_trajectory_if_signal(const gsl_rng *r, const Neuron *neuron,
                              const double *signal, const TimeFrame *time_frame,
                              double *v) {

  v[0] = 0;
  const double dt = time_frame->dt;

  for (size_t i = 0; i < time_frame->N; i++) {
    v[i + 1] = v[i] +
               (neuron->drift(v[i], neuron->if_params) + signal[i]) * dt +
               sqrt(2. * neuron->if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    if (v[i + 1] > 1.0) {
      v[i + 1] = 0.;
    }
  }
}

/*
 * get spike train of an ifac neuron
 * Uses Euler-Maruyama algorithm with the usual fire-and-reset condition.
 */
void get_trajectory_ifac(const gsl_rng *r, const Neuron *neuron,
                         const TimeFrame *time_frame, double *v, double *a) {

  v[0] = 0;
  a[0] = 0;
  const double dt = time_frame->dt;

  for (size_t i = 0; i < time_frame->N; i++) {
    v[i + 1] += (neuron->drift(v[i], neuron->if_params) - a[i]) * dt +
                sqrt(2. * neuron->if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    a[i + 1] = a[i] + -1. / neuron->adapt_params->tau_a * a[i] * dt;
    if (v[i + 1] > 1.0) {
      v[i + 1] = 0.;
     a[i + 1] += neuron->adapt_params->Delta;
    }
  }
}

// get spike train of an ifac neuron with applied signal
void get_trajectory_ifac_signal(const gsl_rng *r, const Neuron *neuron,
                                const double *signal,
                                const TimeFrame *time_frame, double *v,
                                double *a) {

  v[0] = 0;
  a[0] = 0;
  const double dt = time_frame->dt;

  for (size_t i = 0; i < time_frame->N; i++) {
    v[i + 1] +=
        (neuron->drift(v[i], neuron->if_params) - a[i] + signal[i]) * dt +
        sqrt(2. * neuron->if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    a[i + 1] = a[i] + -1. / neuron->adapt_params->tau_a * a[i] * dt;
    if (v[i + 1] > 1.0) {
      v[i + 1] = 0.;
      a[i + 1] += neuron->adapt_params->Delta;
    }
  }
}
