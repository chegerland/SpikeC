#ifndef STATISTICS_H
#define STATISTICS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "spiketrain.h"
#include "timeframe.h"
#include <fftw3.h>

/**
 * @brief Calculates the mean of a given array
 * @param values Array containing values
 * @param N Length of array
 * @return Mean
 */
double mean(const double *values, const int N);

/**
 * @brief Calculates the standard deviation of a given array
 * @param values Array containing values
 * @param N Length of array
 * @return Standard deviation
 */
double standard_deviation(const double *values, const int N);

/**
 * @brief Return number of spikes in spike train
 * @param spike_train Spike train
 * @return Number of spikes
 */
int spike_count(const spike_train_t *spike_train);

/**
 * @brief Returns the spike times from a given spike spike_train
 * @param [in] spike_train Spike spike_train
 * @param [in] time_frame Time frame
 * @param [out] times Spike times
 * @return Number of spikes
 */
int spike_times(const spike_train_t *spike_train,
                const time_frame_t *time_frame, double *times);

/**
 * If an entry of the spike train is true, add 1/(N*dt) to the firing rate.
 * @brief Adds a spike train to the firing rate.
 * @param [in] spike_train
 * @param [in] N Number of neurons
 * @param [in] time_frame Time frame
 * @param [out] firing_rate
 */
void add_to_firing_rate(const spike_train_t *spike_train, int N,
                        const time_frame_t *time_frame, double *firing_rate);

/**
 * We calculate the cross spectrum of a single signal, i.e. the power spectrum
 * \f$ S_{xy}(\omega) = x(\omega)*y^{*}(\omega) / T \f$, where T is the time
 * period of the signals. We will call x the output and y the input signal.
 * Notice that the real cross spectrum is the average over this quantity!
 * @brief Calculates the cross spectrum of two signals.
 * @param [in] input_signal Array containing input signal
 * @param [in] output_signal Array containing output signal
 * @param [in] time_frame Time frame
 * @param [out] spectrum Array containing cross spectrum
 */
void cross_spectrum(double *input_signal, double *output_signal,
                    const time_frame_t *time_frame, fftw_complex *spectrum);

/**
 * @brief Calculates the power spectrum of a given real signal
 * @param [in] signal Array containing the signal
 * @param [in] time_frame Time frame
 * @param [out] spectrum Array containing the power spectrum.
 */
void power_spectrum(double *signal, const time_frame_t *time_frame,
                    double *spectrum);

/**
 * @brief Calculates the susceptibility of the output signal to an input signal.
 * @param [in] input_signal Array containing input signal
 * @param [in] output_signal Array containing output signal
 * @param [in] time_frame Time frame
 * @param [out] suscept Array containing the susceptibility
 */
void susceptibility(double *input_signal, double *output_signal,
                    const time_frame_t *time_frame, fftw_complex *suscept);

#ifdef __cplusplus
}
#endif

#endif // STATISTICS_H
