#include "suscept_sim.h"
#include <math.h>
#include <string.h>

suscept_sim_t *read_suscept_sim(ini_t *ini_file) {

  suscept_sim_t *suscept_sim = malloc(sizeof(suscept_sim_t));

  // read the simulation parameters from ini file
  double c = NAN;
  size_t N_neurons = 0;
  ini_sget(ini_file, "Simulation", "c", "%lf", &c);
  ini_sget(ini_file, "Simulation", "N_neurons", "%zu", &N_neurons);
  suscept_sim->c = c;
  suscept_sim->N_neurons = N_neurons;

  // read time frame from ini file
  suscept_sim->time_frame = read_time_frame(ini_file);

  // read the neuron type
  const char *neuron_type = NULL;
  ini_sget(ini_file, "Neuron", "type", NULL, &neuron_type);

  if (strcmp(neuron_type, "LIFAC") == 0 || strcmp(neuron_type, "PIFAC") == 0) {
    suscept_sim->neuron = read_neuron_ifac(ini_file);
    suscept_sim->get_spike_train = get_spike_train_ifac_signal;
  } else if (strcmp(neuron_type, "LIF") == 0 ||
             strcmp(neuron_type, "PIF") == 0) {
    suscept_sim->neuron = read_neuron_if(ini_file);
    suscept_sim->get_spike_train = get_spike_train_if_signal;
  } else {
    printf("Invalid Neuron type (%s)\n", neuron_type);
    exit(EXIT_FAILURE);
  }

  // change diffusion coefficient of the neuron
  double D = suscept_sim->neuron->if_params->D;
  suscept_sim->neuron->if_params->D = D * (1.0 - c);

  // set strength of white noise
  suscept_sim->alpha = D * c;

  // create arrays
  suscept_sim->suscept_lin = (double complex *)calloc(
      suscept_sim->time_frame->N / 2 + 1, sizeof(double complex));
  suscept_sim->suscept_nonlin = (double complex *)calloc(
      suscept_sim->time_frame->N / 4 + 1, sizeof(double complex));

  return suscept_sim;
}

void print_suscept_sim(FILE *fp, const suscept_sim_t *suscept_sim) {
  print_time_frame(fp, suscept_sim->time_frame);
  fprintf(fp, "#\n");
  print_neuron(fp, suscept_sim->neuron);
  fprintf(fp, "#\n");
  fprintf(fp,
          "# Simulation\n"
          "#\n"
          "# type = suscept_sim\n"
          "# c = %lf\n"
          "# N_neurons = %zu\n",
          suscept_sim->c, suscept_sim->N_neurons);
}

void write_suscepts_to_file(FILE *fp, const suscept_sim_t *suscept_sim) {
  // explain data type
  fprintf(fp, "#\n");
  fprintf(fp, "# Data format: f, Re[chi_1(f)], Im[chi_1(f)], Re[chi_2(f,f)], "
              "Im[chi_2(f,f)]\n");

  double T = suscept_sim->time_frame->t_end - suscept_sim->time_frame->t_0;
  // print results to file
  for (size_t i = 0; i < suscept_sim->time_frame->N / 4 + 1; i++) {
    fprintf(fp, "%f,%f,%f,%f,%f\n", (double)i / T,
            creal(suscept_sim->suscept_lin[i]),
            cimag(suscept_sim->suscept_lin[i]),
            creal(suscept_sim->suscept_nonlin[i]),
            cimag(suscept_sim->suscept_nonlin[i]));
  }
}

void free_suscept_sim(suscept_sim_t *suscept_sim) {
  if (suscept_sim != NULL) {
    free_time_frame(suscept_sim->time_frame);
    free_neuron(suscept_sim->neuron);
    free(suscept_sim->suscept_lin);
    free(suscept_sim->suscept_nonlin);
  }
}
