#ifndef IF_NEURONS_H
#define IF_NEURONS_H

#include "timeframe.h"
#include <gsl/gsl_randist.h>

enum IF_TYPE { LIF, PIF };

typedef struct {
  double mu;
  double D;
} if_params_t;

typedef struct {
  enum IF_TYPE type;
  if_params_t *params;
  double (*drift)(double, int, if_params_t *);
} NeuronIF;

double lif_drift(double v, int i, if_params_t *params);
double pif_drift(double v, int i, if_params_t *params);

NeuronIF *create_neuron_if(double mu, double D, enum IF_TYPE type);

void free_neuron_if(NeuronIF *neuron);

void get_spike_train_if(const gsl_rng *r, NeuronIF *neuron,
                        TimeFrame *time_frame, double *spike_train);
void get_spike_train_if_signal(const gsl_rng *r, NeuronIF *neuron,
                               const double *signal, TimeFrame *time_frame,
                               double *spike_train);
#endif // IF_NEURONS_H
