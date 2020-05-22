#ifndef IFAC_NEURONS_H
#define IFAC_NEURONS_H

#include "if_neurons.h"

enum IFAC_TYPE { LIFAC, PIFAC };

typedef struct {
  double tau_a;
  double Delta;
} adapt_params_t;

typedef struct {
  enum IFAC_TYPE type;
  if_params_t *params;
  adapt_params_t *adapt_params;
  double (*drift)(double, int, if_params_t *);
} NeuronIFAC;

NeuronIFAC *create_neuron_ifac(double mu, double D, double tau_a, double Delta,
                         enum IFAC_TYPE type);

void free_neuron_ifac(NeuronIFAC *neuron);

void get_spike_train_ifac(const gsl_rng *r, NeuronIFAC *neuron,
                          TimeFrame *time_frame, double *spike_train);
void get_spike_train_ifac_signal(const gsl_rng *r, NeuronIFAC *neuron,
                                 const double *signal, TimeFrame *time_frame,
                                 double *spike_train);
#endif // IFAC_NEURONS_H
