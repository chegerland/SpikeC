#include "suscept_sim.h"

#include <math.h>

suscept_sim_t *read_suscept_sim(ini_t *ini_file) {

  suscept_sim_t *suscept_sim =
      (suscept_sim_t *)calloc(1, sizeof(suscept_sim_t));

  // read the two parameters from ini file
  double c = NAN;
  int N_neurons = 0;
  ini_sget(ini_file, "Simulation", "c", "%lf", &c);
  ini_sget(ini_file, "Simulation", "N_neurons", "%d", &N_neurons);
  suscept_sim->c = c;
  suscept_sim->N_neurons = N_neurons;

  // read neuron and time frame from ini file
  suscept_sim->time_frame = read_time_frame(ini_file);
  suscept_sim->neuron = read_neuron_if(ini_file);

  // change diffusion coefficient of neuron
  double D = suscept_sim->neuron->params->D;
  suscept_sim->neuron->params->D = D * (1.0 - c);

  // set strength of white noise
  suscept_sim->alpha = D * c;

  // create arrays
  suscept_sim->suscept_lin = (double complex *)calloc(
      suscept_sim->time_frame->N / 2 + 1, sizeof(double complex));
  suscept_sim->suscept_nonlin = (double complex *)calloc(
      suscept_sim->time_frame->N / 4 + 1, sizeof(double complex));

  return suscept_sim;
}

void print_suscept_sim(FILE *fp, suscept_sim_t *suscept_sim) {
  print_time_frame(fp, suscept_sim->time_frame);
  fprintf(fp, "#\n");
  print_neuron_if(fp, suscept_sim->neuron);
  fprintf(fp, "#\n");
  fprintf(fp,
          "# Simulation\n"
          "#\n"
          "# type = suscept_sim\n"
          "# c = %lf\n"
          "# N_neurons = %d\n",
          suscept_sim->c, suscept_sim->N_neurons);
}

void write_suscepts_to_file(FILE *fp, suscept_sim_t *suscept_sim) {
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
    free_neuron_if(suscept_sim->neuron);
    free(suscept_sim->suscept_lin);
    free(suscept_sim->suscept_nonlin);
  }
}
