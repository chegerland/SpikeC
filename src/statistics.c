#include <complex.h>
#include <fftw3.h>
#include <math.h>
#include <stdlib.h>

#include "statistics.h"
#include "utils/fft.h"

double mean(size_t length, const double *array) {
  double mean = 0;
  for (size_t i = 0; i < length; i++) {
    mean += array[i] / ((double)length);
  }
  return mean;
}

void susceptibility_lin(const double complex *isf, double *spike_train,
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

void susceptibility_lin_nonlin(const double *signal,
                               const double *spike_train,
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
      suscept_nonlin[i*(i + 1)/2 + j] += scale * osf[i + j] * conj(isf[i]) * conj(isf[j]);
    }
  }

  free(osf);
}
