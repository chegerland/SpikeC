#include <complex.h>
#include <fftw3.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <math.h>
#include <stdlib.h>

#include "fft.h"
#include "statistics.h"

double mean(int length, const double *array) {
  double mean = 0;
  for (int i = 0; i < length; i++) {
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
  double complex *osf =
      (double complex *)calloc(length / 2 + 1, sizeof(double complex));

  fft_r2c(length, dt, spike_train, osf);

  // fill susceptibility and normalize appropriately
  for (int i = 0; i < length / 2 + 1; i++) {
    double scale = 1. / ((double)norm * pow(cabs(isf[i]), 2));
    suscept[i] += scale * (osf[i] * conj(isf[i]));
  }

  free(osf);
}

void susceptibility_lin_nonlin(const double complex *isf, double alpha,
                               const double *spike_train,
                               const TimeFrame *time_frame,
                               double complex *suscept_lin,
                               double complex *suscept_nonlin, size_t norm) {

  // length of the signals is N/2 + 1 because we perform real DFT
  size_t length = time_frame->N;
  const double dt = time_frame->dt;
  const double T = time_frame->t_end - time_frame->t_0;

  // fourier transform spiketrain
  double complex *osf =
      (double complex *)calloc(length / 2 + 1, sizeof(double complex));
  fft_r2c(length, dt, spike_train, osf);

  // fill susceptibility and normalize appropriately
  for (int i = 0; i < length / 2 + 1; i++) {
    double scale = 1. / ((double)norm * pow(cabs(isf[i]), 2));
    //double scale = 1. / ((double)norm * 2. * alpha);
    suscept_lin[i] += scale * (osf[i] * conj(isf[i]));
  }

  for (int i = 0; i < length / 4 + 1; i++) {
    double scale = 1. / ((double)norm * 2. * pow(cabs(isf[i]), 4)/T);
    //double scale = 1. / ((double)norm * 2. * pow(2.*alpha, 2));
    suscept_nonlin[i] += scale * (osf[2 * i] * conj(isf[i]) * conj(isf[i]));
  }

  free(osf);
}

void susceptibility_lin_nonlin_matrix(const double complex *isf, double alpha,
                                      const double *spike_train,
                                      const TimeFrame *time_frame,
                                      double complex *suscept_lin,
                                      double complex **suscept_nonlin,
                                      size_t norm) {

  // length of the signals is N/2 + 1 because we perform real DFT
  size_t length = time_frame->N;
  const double dt = time_frame->dt;

  // fourier transform spiketrain
  double complex *osf =
      (double complex *)calloc(length / 2 + 1, sizeof(double complex));
  fft_r2c(length, dt, spike_train, osf);

  // fill susceptibility and normalize appropriately
  for (int i = 0; i < length / 2 + 1; i++) {
    double scale = 1. / ((double)norm * pow(cabs(isf[i]), 2));
    suscept_lin[i] += scale * (osf[i] * conj(isf[i]));
  }

  for (int i = 0; i < length / 4 + 1; i++) {
    for (int j = 0; j < length / 4 + 1; j++) {
      double scale = 1. / ((double)norm * 2. * pow(cabs(isf[i]), 2) *
                           pow(cabs(isf[j]), 2));
      suscept_nonlin[i][j] += scale * osf[i + j] * conj(isf[i]) * conj(isf[j]);
    }
  }

  free(osf);
}
