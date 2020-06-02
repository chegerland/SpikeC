#ifndef SIGNALS_H
#define SIGNALS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "timeframe.h"
#include <complex.h>
#include <fftw3.h>
#include <gsl/gsl_rng.h>

/**
 * @brief Calculates a signal alpha*cos(2*pi*f*t).
 * @param [in] alpha Amplitude
 * @param [in] f Frequency
 * @param [in] time_frame Time frame
 * @param [out] signal Array containing signal values
 */
void cosine_signal(double alpha, double f, const TimeFrame *time_frame,
                   double *signal);

/**
 * @brief Calculates a step signal alpha*Theta(t - t_0).
 * @param [in] alpha  Amplitude
 * @param [in] t_0 Start time
 * @param [in] time_frame Time frame
 * @param [out] signal Array containing signal values
 */
void step_signal(double alpha, double t_0, const TimeFrame *time_frame,
                 double *signal);

/**
 * @brief Calculates a signal alpha*cos(2*pi*f1*t) + beta*cos(2*pi*f2*t + phi)
 * @param [in] alpha Amplitude of first signal
 * @param [in] f1 Frequency of first signal
 * @param [in] beta Amplitude of second signal
 * @param [in] f2 Frequency of second signal
 * @param [in] phi Phase difference between first and second signal
 * @param [in] time_frame Time frame
 * @param [out] signal Array containing signal values
 */
void two_cosine_signal(double alpha, double f1, double beta, double f2,
                       double phi, const TimeFrame *time_frame, double *signal);

/**
 * @brief Generates bandlimited white_noise with an intensity of 2*alpha
 *
 * This routine prepares frequencies with random phase and amplitude equal to
 * sqrt(2*alpha*T), where T is the time frame. We calculate them like this, so
 * that the power spectrum is S = 1/T * (f f^*) = 2 * alpha.
 * The variance of this noise is given by var = 2 * height_of_power_spectrum *
 * (f_high - f_low) = 4*alpha*(f_high - f_low).
 * @param [in] r Pointer to random number generator.
 * @param [in] alpha Intensity parameter
 * @param [in] f_low Lower cut-off frequency
 * @param [in] f_high Upper cut-off frequency
 * @param [in] time_frame Time frame
 * @param [out] signal Array containing signal values
 */
void band_limited_white_noise(const gsl_rng *r, double alpha, double f_low,
                              double f_high, const TimeFrame *time_frame,
                              double *signal);

#ifdef __cplusplus
}
#endif

#endif // SIGNALS_H
