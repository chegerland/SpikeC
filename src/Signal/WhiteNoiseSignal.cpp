#include <fftw3.h>

// json parser
#include <Spike.h>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>

namespace pt = boost::property_tree;

#include "../FFT/fft.h"
#include "WhiteNoiseSignal.h"

// constructor from parameters
WhiteNoiseSignal::WhiteNoiseSignal(
    double alpha, double f_low, double f_high,
    const TimeFrame &time_frame)
    : Signal(time_frame), alpha(alpha), f_low(f_low), f_high(f_high),
      generator(rd()), dist(0.0, 1.0) {
  frequencies.resize(time_frame.get_steps()/2 + 1);
  calculate_signal();
}

WhiteNoiseSignal::WhiteNoiseSignal(
    const std::string &input_file,
    const TimeFrame &time_frame)
    : Signal(time_frame), generator(rd()), dist(0.0, 1.0) {
  pt::ptree root;
  pt::read_json(input_file, root);

  // check if type is right
  auto type = root.get<std::string>("Signal.type");
  assert(type == "white noise");

  // read simulation data into simulation variables
  alpha = root.get<double>("Signal.alpha");
  f_low = root.get<double>("Signal.f_low");
  f_high = root.get<double>("Signal.f_high");
  assert(f_high > f_low && f_low >= 0.);

  frequencies.resize(time_frame.get_steps()/2 + 1);

  // generate the white noise
  calculate_signal();
}

void WhiteNoiseSignal::calculate_signal() {

  const size_t steps = time_frame.get_steps();
  const double dt = time_frame.get_dt();

  // define cut_off indices
  const size_t cut_low = f_low * steps * dt;
  const size_t cut_high = f_high * steps * dt;

  // white noise in frequency space has constant amplitude, random phase
  for (size_t i = 1; i < steps / 2; i++) {
    double rand = dist(generator);
    frequencies[i] = {cos(2.0 * M_PI * rand), sin(2.0 * M_PI * rand)};

    // cut frequencies
    if (i < cut_low || i > cut_high) {
      frequencies[i] = 0.0;
    }
  }

  // DC and Nyquist frequency have to be purely real
  frequencies[0] = 1.0;
  frequencies[steps / 2] = 1.0;

  // normalize frequencies, so that power spectrum = 2*alpha
  for(auto & frequency : frequencies) {
    frequency *= sqrt(2. * alpha * (time_frame.get_t_end() - time_frame.get_t_0()));
  }

  // calculate signal values by fourier transforming from frequencies
  fft_c2r(dt, frequencies, signal_values);
}

// return get_value
double WhiteNoiseSignal::signal(double t) const {
  // check if time is in time frame
  assert(t <= time_frame.get_t_end() && t >= time_frame.get_t_0());

  // calculate according index
  auto index = (size_t)((t - time_frame.get_t_0()) / time_frame.get_dt());

  return signal_values[index];
}

void WhiteNoiseSignal::print_info(std::ofstream &file) const {
  file << "# Signal parameters: "
       << "\n"
       << "# type = white noise\n"
       << "# alpha = " << alpha << "\n"
       << "# f_low = " << f_low << "\n"
       << "# f_high = " << f_high << "\n";
}
