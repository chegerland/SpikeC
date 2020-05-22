#ifndef SIGNALS_H
#define SIGNALS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <fftw3.h>
#include <complex.h>
#include <gsl/gsl_rng.h>
#include "timeframe.h"

//! Calculates a signal alpha*cos(2*pi*f*t)
void cosine_signal(double alpha, double f, const TimeFrame *time_frame,
                   double *signal);

//! Calculates a step signal alpha*Theta(t - t_0)
void step_signal(double alpha, double t_0, const TimeFrame *time_frame,
                 double *signal);

//! Calculates a signal alpha*cos(2*pi*f1*t) + beta*cos(2*pi*f2*t + phi)
void two_cosine_signal(double alpha, double f1, double beta, double f2,
                       double phi, const TimeFrame *time_frame,
                       double *signal);

//! Generates bandlimited white_noise with an intensity of 2*alpha
void band_limited_white_noise(const gsl_rng *r, double alpha, double f_low,
                              double f_high, const TimeFrame *time_frame,
                              double *signal);

#ifdef __cplusplus
}
#endif

#endif // SIGNALS_H
