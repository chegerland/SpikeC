#include "signals.h"
#include <fftw3.h>
#include <gsl/gsl_randist.h>
#include <math.h>

// generate cosine signal
void cosine_signal(const double alpha, const double f,
                   const time_frame_t *time_frame, double *signal) {
  for (int i = 0; i < time_frame->N; i++) {
    signal[i] = alpha * cos(2.0 * M_PI * f * time_frame->t[i]);
  }
}

// generate a step signal
void step_signal(const double alpha, const double t_0,
                 const time_frame_t *time_frame, double *signal) {
  for (int i = 0; i < time_frame->N; i++) {
    if (time_frame->t[i] < t_0) {
      signal[i] = 0.;
    } else {
      signal[i] = alpha;
    }
  }
}

// generate a two cosine signal
void two_cosine_signal(const double alpha, const double f1, const double beta,
                       const double f2, const double phi,
                       const time_frame_t *time_frame, double *signal) {
  for (int i = 0; i < time_frame->N; i++) {
    signal[i] = alpha * cos(2.0 * M_PI * f1 * time_frame->t[i]) +
                beta * cos(2.0 * M_PI * f2 * time_frame->t[i] + phi);
  }
}

void band_limited_white_noise(const gsl_rng *r, double alpha, double f_low, double f_high,
                              const time_frame_t *time_frame, double *signal) {

  // number of steps and time step
  int N = time_frame->N;
  double dt = time_frame->dt;

  // cut-off indices corresponding to the cut-off frequencies
  int cut_high = (int) (f_high * N * dt);
  int cut_low = (int) (f_low * N * dt);

  // define array to hold signal frequencies
  fftw_complex *frequencies;
  frequencies =
      (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * (N / 2 + 1));

  // white noise in frequency space has constant amplitude, random phase
  frequencies[0][0] = 1.0;
  frequencies[0][1] = 0.0;

  // fill first half
  double rand;
  for (int i = 1; i < N / 2; i++) {
    rand = gsl_ran_gaussian(r, 1.0);
    frequencies[i][0] = cos(2.0 * M_PI * rand);
    frequencies[i][1] = sin(2.0 * M_PI * rand);

    if (i > cut_high) {
      frequencies[i][0] = 0.0;
      frequencies[i][1] = 0.0;
    }

    if (i < cut_low) {
      frequencies[i][0] = 0.0;
      frequencies[i][1] = 0.0;
    }
  }

  frequencies[N / 2][0] = 1.0;
  frequencies[N / 2][1] = 0.0;

  // calculate signal by fourier transforming from frequencies
  fftw_plan p;
  p = fftw_plan_dft_c2r_1d(N, frequencies, signal, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  fftw_free(frequencies);

  // normalise signal because we transform backward
  double scale = 1. / ((double)N * dt);
  for (int i = 0; i < N; i++) {
    signal[i] = alpha * scale * signal[i];
  }
}
