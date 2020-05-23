#ifndef NEURONS_H
#define NEURONS_H

#include "timeframe.h"
#include <gsl/gsl_randist.h>
#include <stdbool.h>

enum NEURON_TYPE { LIF, PIF, LIFAC, PIFAC };
extern const char *neuron_type_names[];

//! Parameters for integrate-and-fire neurons
typedef struct {
  double mu; ///< mean input current
  double D;  ///< diffusion coefficient
} if_params_t;

typedef struct {
  double tau_a; ///< adaptation time constant
  double Delta; ///< kick size of the adaptation
} adapt_params_t;

//! An integrate-and-fire neuron
typedef struct {
  enum NEURON_TYPE type;                       ///< type of the IF neuron
  if_params_t *if_params;                         ///< parameters of the IF neuron
  adapt_params_t *adapt_params;                ///< parameters of the adaptation
  double (*drift)(double, int, if_params_t *); ///< drift of the IF neuron
} Neuron;

bool is_ifac(enum NEURON_TYPE type);

double lif_drift(double v, int i, if_params_t *params);
double pif_drift(double v, int i, if_params_t *params);

Neuron *create_neuron_if(double mu, double D, enum NEURON_TYPE type);
Neuron *create_neuron_ifac(double mu, double D, double tau_a, double Delta,
                           enum NEURON_TYPE type);
Neuron *read_neuron_if(ini_t *ini_file);
Neuron *read_neuron_ifac(ini_t *ini_file);

void free_neuron(Neuron *neuron);
void print_neuron(FILE *fp, Neuron *neuron);

void get_spike_train_if(const gsl_rng *r, Neuron *neuron,
                        TimeFrame *time_frame, double *spike_train);
void get_spike_train_if_signal(const gsl_rng *r, Neuron *neuron,
                               const double *signal, TimeFrame *time_frame,
                               double *spike_train);
void get_spike_train_ifac(const gsl_rng *r, Neuron *neuron,
                        TimeFrame *time_frame, double *spike_train);
void get_spike_train_ifac_signal(const gsl_rng *r, Neuron *neuron,
                               const double *signal, TimeFrame *time_frame,
                               double *spike_train);

#endif // NEURONS_H
