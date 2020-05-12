#ifndef IF_NEURONS_H
#define IF_NEURONS_H

#include "../timeframe.h"
#include "../utils/ini.h"
#include <gsl/gsl_randist.h>

//! Integrate-and-fire types (perfect, leaky, ...)
enum IF_TYPE { LIF, PIF };

//! Names (i.e. strings) corresponding to the IF_TYPEs
extern const char *if_type_names[];

//! Parameters for integrate-and-fire neurons
typedef struct {
  double mu; ///< mean input current
  double D;  ///< diffusion coefficient
} if_params_t;

//! An integrate-and-fire neuron
typedef struct {
  enum IF_TYPE type;                           ///< type of the IF neuron
  if_params_t *params;                         ///< parameters of the IF neuron
  double (*drift)(double, int, if_params_t *); ///< drift of the IF neuron
} NeuronIF;

double lif_drift(double v, int i, if_params_t *params);
double pif_drift(double v, int i, if_params_t *params);

NeuronIF *create_neuron_if(double mu, double D, enum IF_TYPE type);
NeuronIF *read_neuron_if(ini_t *ini_file);

void free_neuron_if(NeuronIF *neuron);
void print_neuron_if(FILE *fp, NeuronIF *neuron);

void get_spike_train_if(const gsl_rng *r, NeuronIF *neuron,
                        TimeFrame *time_frame, double *spike_train);
void get_spike_train_if_signal(const gsl_rng *r, NeuronIF *neuron,
                               const double *signal, TimeFrame *time_frame,
                               double *spike_train);
#endif // IF_NEURONS_H
