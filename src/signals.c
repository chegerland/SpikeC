#include <gsl/gsl_randist.h>
#include <math.h>

#include "signals.h"
#include "statistics.h"
#include "utils/fft.h"

// generate cosine signal alpha*cos(2*pi*f*t)
void cosine_signal(const double alpha, const double f,
                   const TimeFrame *time_frame, double *signal) {
  for (int i = 0; i < time_frame->N; i++) {
    signal[i] = alpha * cos(2.0 * M_PI * f * time_frame->t[i]);
  }
}

// generate a step signal alpha*theta(t - t_0)
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

/*
 * generate a two cosine signal
 * alpha*cos(2*pi*f1*t) + beta*cos(2*pi*f2*t + beta)
 */
void two_cosine_signal(const double alpha, const double f1, const double beta,
                       const double f2, const double phi,
                       const TimeFrame *time_frame, double *signal) {
  for (int i = 0; i < time_frame->N; i++) {
    signal[i] = alpha * cos(2.0 * M_PI * f1 * time_frame->t[i]) +
                beta * cos(2.0 * M_PI * f2 * time_frame->t[i] + phi);
  }
}

/*
 * generate band limited gaussian white noise.
 * The power spectrum of this noise has height 2*alpha and the variance is given
 * by var = 2*height_of_power_spectrum*(f_high - f_low).
 */
void band_limited_white_noise(const gsl_rng *r, double alpha, double f_low,
                              double f_high, const TimeFrame *time_frame,
                              double *signal) {

  // number of steps and time step
  const size_t N = time_frame->N;
  const double dt = time_frame->dt;

  // cut-off indices corresponding to the cut-off frequencies
  const size_t cut_low = (size_t)(f_low * N * dt);
  const size_t cut_high = (size_t)(f_high * N * dt);

  /*
   * we set the amplitude of the complex frequencies to sqrt(2*alpha*T)
   * so that the power spectrum is S = 1/T * f * f^* == 2*alpha.
   */
  const double height =
      sqrt(2. * alpha * (time_frame->t_end - time_frame->t_0));

  // array for frequencies
  double complex freqs[N / 2 + 1];

  // white noise in frequency space has constant amplitude, random phase
  for (size_t i = 1; i < N / 2 + 1; i++) {
    double rand = gsl_ran_gaussian(r, 1.0);
    freqs[i] =
        height * (cos(2.0 * M_PI * rand) - _Complex_I * sin(2.0 * M_PI * rand));

    if ((i > cut_high) || (i < cut_low)) {
      freqs[i] = 0.0;
    }
  }

  // dc component and nyquist are purely real
  freqs[0] = height;
  freqs[N / 2] = height;

  // calculate signal by fourier transforming from frequencies
  fft_c2r(N, dt, freqs, signal);

  // subtract mean from signal
  double mean_signal = mean(N, signal);
  for (int i = 0; i < N; i++) {
    signal[i] -= mean_signal;
  }
}
