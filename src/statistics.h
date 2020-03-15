#ifndef STATISTICS_H
#define STATISTICS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "spiketrain.h"
#include "timeframe.h"

/**
 * @brief Returns the spike times from a given spike spike_train
 * @param [out] times Spike times
 * @param [in] spike_train Spike spike_train
 * @param [in] time_frame Time frame
 * @return Number of spikes
 */
int spike_times(double *times, const spike_train_t *spike_train,
                const time_frame_t *time_frame);

/**
 * @brief Return number of spikes in spike train
 * @param spike_train Spike train
 * @return Number of spikes
 */
int spike_count(const spike_train_t *spike_train);

/**
 * If an entry of the spike train is true, add 1/(N*dt) to the firing rate.
 * @brief Adds a spike train to the firing rate.
 * @param [out] firing_rate
 * @param N Number of neurons
 * @param [in] spike_train
 */
void add_to_firing_rate(double *firing_rate, int N,
                        const spike_train_t *spike_train,
                        const time_frame_t *time_frame);

#ifdef __cplusplus
}
#endif

#endif // STATISTICS_H
