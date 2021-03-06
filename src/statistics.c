#include <complex.h>
#include <fftw3.h>
#include <math.h>
#include <stdlib.h>

#include "statistics.h"
#include "utils/fft.h"

// calculates the arithmetic mean of an array of size length
double mean(size_t length, const double *array) {
  double mean = 0;
  for (size_t i = 0; i < length; i++) {
    mean += array[i];
  }
  return mean / ((double)length);
}

// calculates the variance of an array of size length
double variance(size_t length, const double *array) {
  double var = 0.0;
  double array_mean = mean(length, array);
  for (size_t i = 0; i < length; i++) {
    var += 1. / ((double)length) * pow(array[i] - array_mean, 2);
  }

  return var;
}

// calculates the coefficient of variation of an array of size length
double calculate_cv(size_t length, double *array) {
  double array_mean = mean(length, array);
  double array_std = sqrt(variance(length, array));

  return array_std / array_mean;
}

// calculates the number of spikes in a spike train.
size_t spike_count(size_t length, const double *spike_train) {
  size_t count = 0;

  for (size_t i = 0; i < length; i++) {
    if (spike_train[i] != 0) {
      count++;
    }
  }

  return count;
}

// calculates the interspike intervals from a given spike train
size_t calculate_isi(const TimeFrame *time_frame, const double *spike_train,
                     double *spike_times) {

  size_t last_index = 0;        // last index a spike happened
  size_t spike_times_count = 0; // number of interspike intervals

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

/*
 * calculate power spectrum
 * Each entry is divided by norm (for averaging purposes).
 */
void power_spectrum(const double *signal, const TimeFrame *time_frame,
                    double *spectrum, const size_t norm) {
  // length of the signals is N/2 + 1 because we perform real DFT
  size_t length = time_frame->N;
  const double dt = time_frame->dt;

  // fourier transform signal
  double complex *signal_fourier =
      malloc((length / 2 + 1) * sizeof(double complex));
  fft_r2c(length, dt, signal, signal_fourier);

  // calculate power spectrum
  for (size_t i = 0; i < length / 2 + 1; i++) {
    double scale = 1. / ((double)norm * (time_frame->t_end - time_frame->t_0));
    spectrum[i] += scale * cabs(signal_fourier[i]);
  }

  // free memory
  free(signal_fourier);
}

/*
 * calculate cross spectrum
 * Each entry is divided by norm (for averaging purposes).
 */
void cross_spectrum(const double *first_signal, const double *second_signal,
                    const TimeFrame *time_frame, double complex *spectrum,
                    const size_t norm) {
  // length of the signals is N/2 + 1 because we perform real DFT
  size_t length = time_frame->N;
  const double dt = time_frame->dt;

  // fourier transform spiketrain
  double complex *first_signal_fourier =
      malloc((length / 2 + 1) * sizeof(double complex));
  double complex *second_signal_fourier =
      malloc((length / 2 + 1) * sizeof(double complex));
  fft_r2c(length, dt, first_signal, first_signal_fourier);
  fft_r2c(length, dt, second_signal, second_signal_fourier);

  // calculate crossspectrum
  for (size_t i = 0; i < length / 2 + 1; i++) {
    double scale = 1. / ((double)norm * (time_frame->t_end - time_frame->t_0));
    spectrum[i] +=
        scale * (first_signal_fourier[i] * conj(second_signal_fourier[i]));
  }

  // free memory
  free(first_signal_fourier);
  free(second_signal_fourier);
}

/*
 * calculate the linear order susceptibility
 * Each entry is divided by norm (for averaging purposes).
 */
void susceptibility_lin(const double *input_signal, const double *output_signal,
                        const TimeFrame *time_frame, double complex *suscept,
                        const size_t norm) {

  // length of the signals is N/2 + 1 because we perform real DFT
  size_t length = time_frame->N;
  const double dt = time_frame->dt;

  // fourier transform spiketrain
  double complex *input_signal_fourier =
      malloc((length / 2 + 1) * sizeof(double complex));
  double complex *output_signal_fourier =
      malloc((length / 2 + 1) * sizeof(double complex));

  fft_r2c(length, dt, input_signal, input_signal_fourier);
  fft_r2c(length, dt, output_signal, output_signal_fourier);

  // calculate susceptibility
  for (size_t i = 0; i < length / 2 + 1; i++) {
    double scale = 1. / ((double)norm * pow(cabs(input_signal_fourier[i]), 2));
    suscept[i] += scale * (output_signal_fourier[i] * conj(input_signal[i]));
  }

  free(input_signal_fourier);
  free(output_signal_fourier);
}

/*
 * calculate the first (lin) and second (nonlin) order susceptibility.
 * Each entry is divided by norm (for averaging purposes).
 * This function only calculates the diagonal terms of the nonlinear
 * susceptibility.
 */
void susceptibility_lin_nonlin(const double *input_signal,
                               const double *output_signal,
                               const TimeFrame *time_frame,
                               double complex *suscept_lin,
                               double complex *suscept_nonlin,
                               const size_t norm) {

  // length of the signals is N/2 + 1 because we perform real DFT
  size_t length = time_frame->N;
  const double dt = time_frame->dt;

  // fourier transform input and output signal
  double complex *input_signal_fourier =
      malloc((length / 2 + 1) * sizeof(double complex));
  double complex *output_signal_fourier =
      malloc((length / 2 + 1) * sizeof(double complex));
  fft_r2c(length, dt, input_signal, input_signal_fourier);
  fft_r2c(length, dt, output_signal, output_signal_fourier);

  // calculate linear susceptibility
  for (size_t i = 0; i < length / 2 + 1; i++) {
    double scale = 1. / ((double)norm * pow(cabs(input_signal_fourier[i]), 2));
    suscept_lin[i] +=
        scale * (output_signal_fourier[i] * conj(input_signal_fourier[i]));
  }

  /*
   * fill nonlinear susceptibility and normalize appropriately
   * ATTENTION: Notice that the bispectrum is only normalized by 1/T and the
   * power spectra are each (!) with 1/T, resulting in an overall
   * factor of 1/T / (1/T^2) = T!
   */
  for (size_t i = 0; i < length / 4 + 1; i++) {
    double scale = (time_frame->t_end - time_frame->t_0) /
                   ((double)norm * 2. * pow(cabs(input_signal_fourier[i]), 4));
    suscept_nonlin[i] +=
        scale * (output_signal_fourier[i + i] * conj(input_signal_fourier[i]) *
                 conj(input_signal_fourier[i]));
  }

  // free memory
  free(input_signal_fourier);
  free(output_signal_fourier);
}

// calculate the first (lin) and second (nonlin) order susceptibility
// this function calculates the nonlinear susceptibility fully, i.e. it returns
// a tridiagonal matrix
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
