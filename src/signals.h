#ifndef SIGNALS_H
#define SIGNALS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <gsl/gsl_rng.h>
#include "timeframe.h"

/**
 * @brief Calculates a signal alpha*cos(2*pi*f*t)
 * @param [in] alpha Amplitude
 * @param [in] f Frequency
 * @param [in] time_frame Time frame
 * @param [out] signal Array containing the signal
 */
void cosine_signal(double alpha, double f, const time_frame_t *time_frame,
                   double *signal);

/**
 * @brief Calculates a step signal alpha*Theta(t - t_0)
 * @param [in] alpha Amplitude
 * @param [in] t_0 Starting time
 * @param [in] time_frame Time frame
 * @param [out] signal Array containing the signal
 */
void step_signal(double alpha, double t_0, const time_frame_t *time_frame,
                 double *signal);

/**
 * @brief Calculates a signal alpha*cos(2*pi*f1*t) + beta*cos(2*pi*f2*t + phi)
 * @param [in] alpha Amplitude of first signal
 * @param [in] f1 Frequency of first signal
 * @param [in] beta Amplitude of second signal
 * @param [in] f2 Frequency of second signal
 * @param [in] phi Phase shift
 * @param [in] time_frame Time frame
 * @param [out] signal Array containing the signal
 */
void two_cosine_signal(double alpha, double f1, double beta, double f2,
                       double phi, const time_frame_t *time_frame,
                       double *signal);

/**
 * The generated signal has standard deviation of 1.
 * @brief Generates bandlimited white_noise
 * @param [in] r Random number generator
 * @param [in] f_low Lower cut-off frequency
 * @param [in] f_high Higher cut-off frequency
 * @param [in] time_frame Time frame
 * @param [out] signal Array containing the signal
 */
void band_limited_white_noise(const gsl_rng *r, double f_low, double f_high,
                             const time_frame_t *time_frame, double *signal);

#ifdef __cplusplus
}
#endif

#endif // SIGNALS_H
