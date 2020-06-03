#include <complex.h>
#include <fftw3.h>
#include <math.h>
#include <stdlib.h>

#include "statistics.h"
#include "utils/fft.h"

double mean(size_t length, const double *array) {
  double mean = 0;
  for (size_t i = 0; i < length; i++) {
    mean += array[i];
  }
  return mean / ((double)length);
}

double variance(size_t length, const double *array) {
  double var = 0.0;
  double array_mean = mean(length, array);
  for (size_t i = 0; i < length; i++) {
    var += 1. / ((double)length) * pow(array[i] - array_mean, 2);
  }

  return var;
}

double calculate_cv(size_t length, double *array) {
  double array_mean = mean(length, array);
  double array_std = sqrt(variance(length, array));

  return array_std / array_mean;
}

int spike_count(size_t length, const double *spike_train) {
  int count = 0;

  for (size_t i = 0; i < length; i++) {
    if (spike_train[i] != 0) {
      count++;
    }
  }

  return count;
}

int calculate_spike_times(const TimeFrame *time_frame,
                          const double *spike_train, double *spike_times) {

  int last_index = 0;        ///< last index a spike happened
  int spike_times_count = 0; ///< number of interspike intervals

  // loop over the whole spike train
  for (size_t i = 1; i < time_frame->N; i++) {

    // if the neuron has spiked
    if (spike_train[i] != 0) {

      // add interspike interval to spike_times array
      spike_times[spike_times_count] =
          time_frame->t[i] - time_frame->t[last_index];

      last_index = i;
      spike_times_count++;
    }
  }

  // reallocate memory for spike_times
  spike_times = realloc(spike_times, spike_times_count * sizeof(double));

  return spike_times_count;
}

void power_spectrum(const double *signal, const TimeFrame *time_frame,
                    double *spectrum, size_t norm) {
  // length of the signals is N/2 + 1 because we perform real DFT
  size_t length = time_frame->N;
  const double dt = time_frame->dt;

  // fourier transform spiketrain
  double complex *sf = malloc((length / 2 + 1) * sizeof(double complex));
  fft_r2c(length, dt, signal, sf);

  // fill susceptibility and normalize appropriately
  for (size_t i = 0; i < length / 2 + 1; i++) {
    double scale = 1. / ((double)norm * (time_frame->t_end - time_frame->t_0));
    spectrum[i] += scale * cabs(sf[i]);
  }

  // free memory
  free(sf);
}

void cross_spectrum(const double *first_signal, const double *second_signal,
                    const TimeFrame *time_frame, double complex *spectrum,
                    size_t norm) {
  // length of the signals is N/2 + 1 because we perform real DFT
  size_t length = time_frame->N;
  const double dt = time_frame->dt;

  // fourier transform spiketrain
  double complex *sf1 = malloc((length / 2 + 1) * sizeof(double complex));
  double complex *sf2 = malloc((length / 2 + 1) * sizeof(double complex));
  fft_r2c(length, dt, first_signal, sf1);
  fft_r2c(length, dt, second_signal, sf2);

  // fill susceptibility and normalize appropriately
  for (size_t i = 0; i < length / 2 + 1; i++) {
    double scale = 1. / ((double)norm * (time_frame->t_end - time_frame->t_0));
    spectrum[i] += scale * (sf1[i] * conj(sf2[i]));
  }

  // free memory
  free(sf1);
  free(sf2);
}

void susceptibility_lin(const double complex *isf, const double *spike_train,
                        const TimeFrame *time_frame, double complex *suscept,
                        size_t norm) {

  // length of the signals is N/2 + 1 because we perform real DFT
  size_t length = time_frame->N;
  const double dt = time_frame->dt;

  // fourier transform spiketrain
  double complex *osf = malloc((length / 2 + 1) * sizeof(double complex));

  fft_r2c(length, dt, spike_train, osf);

  // fill susceptibility and normalize appropriately
  for (size_t i = 0; i < length / 2 + 1; i++) {
    double scale = 1. / ((double)norm * pow(cabs(isf[i]), 2));
    suscept[i] += scale * (osf[i] * conj(isf[i]));
  }

  free(osf);
}

void susceptibility_lin_nonlin(const double *signal, const double *spike_train,
                               const TimeFrame *time_frame,
                               double complex *suscept_lin,
                               double complex *suscept_nonlin, size_t norm) {

  // length of the signals is N/2 + 1 because we perform real DFT
  size_t length = time_frame->N;
  const double dt = time_frame->dt;

  // fourier transform input signal
  double complex *isf = malloc((length / 2 + 1) * sizeof(double complex));
  fft_r2c(length, dt, signal, isf);

  // fourier transform spiketrain
  double complex *osf = malloc((length / 2 + 1) * sizeof(double complex));
  fft_r2c(length, dt, spike_train, osf);

  // fill linear susceptibility and normalize appropriately
  for (size_t i = 0; i < length / 2 + 1; i++) {
    double scale = 1. / ((double)norm * pow(cabs(isf[i]), 2));
    suscept_lin[i] += scale * (osf[i] * conj(isf[i]));
  }

  // fill nonlinear susceptibility and normalize appropriately
  // ATTENTION: Notice that the bispectrum is only normalized by 1/T and the
  // power spectra are also normalized with 1/T, resulting in an overall all
  // factor of 1/T / (1/T^2) = T!
  const double T = time_frame->t_end - time_frame->t_0;
  for (size_t i = 0; i < length / 4 + 1; i++) {
    double scale = T / ((double)norm * 2. * pow(cabs(isf[i]), 4));
    suscept_nonlin[i] += scale * (osf[2 * i] * conj(isf[i]) * conj(isf[i]));
  }

  free(isf);
  free(osf);
}

void susceptibility_lin_nonlin_matrix(const double complex *isf, double alpha,
                                      const double *spike_train,
                                      const TimeFrame *time_frame,
                                      double complex *suscept_lin,
                                      double complex *suscept_nonlin,
                                      size_t norm) {

  // length of the signals is N/2 + 1 because we perform real DFT
  size_t length = time_frame->N;
  const double dt = time_frame->dt;

  // fourier transform spiketrain
  double complex *osf = malloc((length / 2 + 1) * sizeof(double complex));
  fft_r2c(length, dt, spike_train, osf);

  // fill susceptibility and normalize appropriately
  for (size_t i = 0; i < length / 2 + 1; i++) {
    double scale = 1. / ((double)norm * pow(cabs(isf[i]), 2));
    suscept_lin[i] += scale * (osf[i] * conj(isf[i]));
  }

  // use triangular matrix for storage (https://stackoverflow.com/a/17606716)
  for (size_t i = 0; i < length / 4 + 1; i++) {
    for (size_t j = 0; j <= i; j++) {
      double scale = 1. / ((double)norm * 2. * pow(cabs(isf[i]), 2) *
                           pow(cabs(isf[j]), 2));
      suscept_nonlin[i * (i + 1) / 2 + j] +=
          scale * osf[i + j] * conj(isf[i]) * conj(isf[j]);
    }
  }

  free(osf);
}
