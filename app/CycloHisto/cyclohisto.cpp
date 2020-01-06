#include <iostream>

#include "Spike.h"

// main
int main(int argc, char *argv[])
{
  // get command line options
  Options options(argc, argv);

  // define LIF neuron with adaptation
  LIF lif(options.get_file());
  CosineSignal signal(options.get_file());

  // define simulation time frame
  Timeframe time(0.0, 1000.0, 1e-2);

  // array to put firing rate into
  std::vector<double> rate;

  // get firing rate
  lif.firing_rate(rate, &time, &signal);

  // get steps during one period
  int period = (int) 1.0 / (signal.get_f() * time.get_dt());

  // fill array with one period
  double rate_one_period[period] = { 0 };
  for (int i = 0; i < time.get_steps(); i++)
  {
    rate_one_period[i % period] += (double)(period)/(double) time.get_steps() * rate[i];
  };

  // print firing rate to std
  double t = time.get_t_0();
  for (int i = 0; i < period; i++)
  {
    t += time.get_dt();
    std::cout << t << " " << rate_one_period[i] << std::endl;
  };



  return 0;
};
