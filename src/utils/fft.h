#ifndef FFT_H
#define FFT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <complex.h>
#include <fftw3.h>

void fft_r2c(int length, double dt, const double *signal,
             double complex *signal_fourier);
void fft_c2r(int length, double dt, const double complex *signal_fourier,
             double *signal);

#ifdef __cplusplus
}
#endif

#endif // FFT_H
