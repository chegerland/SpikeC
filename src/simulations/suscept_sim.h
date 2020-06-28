#ifndef SUSCEPT_SIM_H
#define SUSCEPT_SIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../neurons.h"
#include "../timeframe.h"
#include "../spiketrain.h"
#include "../utils/ini.h"
#include <complex.h>

// a struct for a susceptibility simulation
typedef struct {
  TimeFrame *time_frame;
  Neuron *neuron;
  void (*get_spike_train)(const gsl_rng *r, const Neuron *neuron,
                          const double *signal, const SpikeTrain *spike_train);

  double c;
  double alpha;
  size_t N_neurons;

  double complex *suscept_lin;
  double complex *suscept_nonlin;
} suscept_sim_t;

suscept_sim_t *read_suscept_sim(ini_t *ini_file);

void print_suscept_sim(FILE *fp, const suscept_sim_t *suscept_sim);
void write_suscepts_to_file(FILE *fp, const suscept_sim_t *suscept_sim);
void free_suscept_sim(suscept_sim_t *suscept_sim);

#ifdef __cplusplus
}
#endif

#endif // SUSCEPT_SIM_H
