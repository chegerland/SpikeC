#ifndef FFT_H
#define FFT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <complex.h>
#include <fftw3.h>

inline void fft_r2c(int length, double dt, const double *signal,
                    double complex *signal_fourier) {
  fftw_plan p = NULL;
#pragma omp critical
  p = fftw_plan_dft_r2c_1d(length, (double *)signal, (fftw_complex *)signal_fourier,
                           FFTW_ESTIMATE);
  fftw_execute(p);
#pragma omp critical
  fftw_destroy_plan(p);

  for (int i = 0; i < length/2 + 1; i++) {
    signal_fourier[i] *= dt;
  }
}

inline void fft_c2r(int length, double dt, const double complex *signal_fourier,
                    double *signal) {
  fftw_plan p = NULL;
#pragma omp critical
  p = fftw_plan_dft_c2r_1d(length, (fftw_complex *)signal_fourier, signal,
                           FFTW_ESTIMATE);
  fftw_execute(p);
#pragma omp critical
  fftw_destroy_plan(p);


  for (int i = 0; i < length; i++) {
    signal[i] /= (double) length * dt;
  }
}

#ifdef __cplusplus
}
#endif

#endif // FFT_H
