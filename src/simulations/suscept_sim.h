#ifndef SUSCEPT_SIM_H
#define SUSCEPT_SIM_H

#include "../neurons/if_neurons.h"
#include "../timeframe.h"
#include "../utils/ini.h"
#include <complex.h>

typedef struct {
  TimeFrame *time_frame;
  NeuronIF *neuron;

  double c;
  double alpha;
  int N_neurons;

  double complex *suscept_lin;
  double complex *suscept_nonlin;
} suscept_sim_t;

suscept_sim_t *read_suscept_sim(ini_t *ini_file);

void print_suscept_sim(FILE *fp, suscept_sim_t *suscept_sim);
void write_suscepts_to_file(FILE *fp, suscept_sim_t *suscept_sim);
void free_suscept_sim(suscept_sim_t *suscept_sim);

#endif // SUSCEPT_SIM_H
