#ifndef NEURONS_H
#define NEURONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "timeframe.h"
#include <gsl/gsl_randist.h>
#include <stdbool.h>

// Neuron types (IF = integrate-and-fire, IFAC = IF with adaptation current)
enum NEURON_TYPE { LIF, PIF, LIFAC, PIFAC };
extern const char *neuron_type_names[];

// Parameters for integrate-and-fire neurons
typedef struct {
  double mu; // mean input current
  double D;  // diffusion coefficient
} if_params_t;

// Parameters for adaptation
typedef struct {
  double tau_a; // adaptation time constant
  double Delta; // kick size of the adaptation
} adapt_params_t;

//! Integrate-and-fire neuron type with adaptation
typedef struct {
  enum NEURON_TYPE type;
  if_params_t *if_params;
  adapt_params_t *adapt_params;
  double (*drift)(double, const if_params_t *);
} Neuron;

bool is_ifac(enum NEURON_TYPE type);

// drift functions
double lif_drift(double v, const if_params_t *params);
double pif_drift(double v, const if_params_t *params);

// initializers from parameters and from ini file
Neuron *create_neuron_if(double mu, double D, enum NEURON_TYPE type);
Neuron *create_neuron_ifac(double mu, double D, double tau_a, double Delta,
                           enum NEURON_TYPE type);
Neuron *read_neuron(ini_t *ini_file);

void free_neuron(Neuron *neuron);
void print_neuron(FILE *stream, const Neuron *neuron);

// functions to obtain spike train from neuron
void get_spike_train_if(const gsl_rng *r, const Neuron *neuron,
                        const TimeFrame *time_frame, double *spike_train);
void get_spike_train_if_signal(const gsl_rng *r, const Neuron *neuron,
                               const double *signal,
                               const TimeFrame *time_frame,
                               double *spike_train);
void get_spike_train_ifac(const gsl_rng *r, const Neuron *neuron,
                          const TimeFrame *time_frame, double *spike_train);
void get_spike_train_ifac_signal(const gsl_rng *r, const Neuron *neuron,
                                 const double *signal,
                                 const TimeFrame *time_frame,
                                 double *spike_train);

// functions to obtain trajectories
void get_trajectory_if(const gsl_rng *r, const Neuron *neuron,
                       const TimeFrame *time_frame, double *v);
void get_trajectory_if_signal(const gsl_rng *r, const Neuron *neuron,
                              const double *signal, const TimeFrame *time_frame,
                              double *v);
void get_trajectory_ifac(const gsl_rng *r, const Neuron *neuron,
                         const TimeFrame *time_frame, double *v, double *a);
void get_trajectory_ifac_signal(const gsl_rng *r, const Neuron *neuron,
                                const double *signal,
                                const TimeFrame *time_frame, double *v,
                                double *a);

#ifdef __cplusplus
}
#endif

#endif // NEURONS_H
