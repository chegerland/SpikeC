#include <fstream>
#include <iostream>

#include "../../extern/ProgressBar.hpp"
#include "Spike.h"

// main
int main(int argc, char *argv[]) {

  // get file from command line
  Options opts(argc, argv);
  std::string parameters = opts.get_input_file();

  // define LIF neuron with adaptation and signal
  LIF neuron(parameters);
  Signal *signal = SignalFactory::create(parameters);
  ExpAdaptation adapt(parameters);

  // define simulation time frame
  Timeframe time(parameters);

  // array to put firing rate into
  std::vector<double> rate;
  rate.resize(time.get_steps());

  // get firing rate
  int N_sims = 100000;

  ProgressBar progbar(N_sims, 70);

#pragma omp parallel for
  for (int j = 0; j < N_sims; j++) {
    std::vector<bool> spike_train =
        neuron.get_spike_train(time, *signal, adapt);
    add_to_firing_rate(spike_train, time, N_sims, rate);

// Progress
#pragma omp critical
    {
      ++progbar;
      progbar.display();
    };
  };

  // print firing rate to file
  std::ofstream file;
  file.open(opts.get_output_file());

  double t = time.get_t_0();
  for (unsigned int i = 0; i < time.get_steps(); i++) {
    t += time.get_dt();
    file << t << "," << (double)rate[i] << "\n";
  };

  progbar.done();
  file.close();

  return 0;
};
