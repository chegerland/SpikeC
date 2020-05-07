#include <gsl/gsl_randist.h>
#include <math.h>

#include "signals.h"
#include "fft.h"
#include "statistics.h"

// generate cosine signal
void cosine_signal(const double alpha, const double f,
                   const TimeFrame *time_frame, double *signal) {
  for (int i = 0; i < time_frame->N; i++) {
    signal[i] = alpha * cos(2.0 * M_PI * f * time_frame->t[i]);
  }
}

// generate a step signal
void step_signal(const double alpha, const double t_0,
                 const TimeFrame *time_frame, double *signal) {
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
                       const TimeFrame *time_frame, double *signal) {
  for (int i = 0; i < time_frame->N; i++) {
    signal[i] = alpha * cos(2.0 * M_PI * f1 * time_frame->t[i]) +
                beta * cos(2.0 * M_PI * f2 * time_frame->t[i] + phi);
  }
}

void band_limited_white_noise(const gsl_rng *r, double alpha, double f_low,
                              double f_high, const TimeFrame *time_frame,
                              double *signal, double complex *frequencies) {

  // number of steps and time step
  const int N = time_frame->N;
  const double dt = time_frame->dt;

  // cut-off indices corresponding to the cut-off frequencies
  const size_t cut_low = (size_t)(f_low * N * dt);
  const size_t cut_high = (size_t)(f_high * N * dt);

  // normalization
  //double height = sqrt(2. * alpha);
  double height = sqrt(2. * alpha * (time_frame->t_end - time_frame->t_0));

  double complex freqs[time_frame->N / 2 + 1];

  // white noise in frequency space has constant amplitude, random phase
  for (int i = 1; i < N / 2; i++) {
    double rand = gsl_ran_gaussian(r, 1.0);
    freqs[i] =
        height * (cos(2.0 * M_PI * rand) - _Complex_I * sin(2.0 * M_PI * rand));

    if (i > cut_high || i < cut_low) {
      freqs[i] = 0.0;
    }
  }

  // dc component and nyquist are purely real
  freqs[0] = height;
  freqs[N / 2] = height;

  // calculate signal by fourier transforming from frequencies
  fft_c2r(N, dt, freqs, signal);

  // subsctract mean from signal
  double mean_signal = mean(N, signal);
  for (int i = 0; i < N; i++) {
    signal[i] -= mean_signal;
  }

  // calculate frequencies by fourier transforming signal
  // TODO: this is because c2r destroys the frequencies
  fft_r2c(N, dt, signal, frequencies);
}
