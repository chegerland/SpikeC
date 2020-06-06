#ifndef SIGNALS_H
#define SIGNALS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "timeframe.h"
#include <complex.h>
#include <fftw3.h>
#include <gsl/gsl_rng.h>

void cosine_signal(double alpha, double f, const TimeFrame *time_frame,
                   double *signal);
void step_signal(double alpha, double t_0, const TimeFrame *time_frame,
                 double *signal);
void two_cosine_signal(double alpha, double f1, double beta, double f2,
                       double phi, const TimeFrame *time_frame, double *signal);
void band_limited_white_noise(const gsl_rng *r, double alpha, double f_low,
                              double f_high, const TimeFrame *time_frame,
                              double *signal);

#ifdef __cplusplus
}
#endif

#endif // SIGNALS_H
