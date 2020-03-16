#ifndef SPIKETRAIN_H
#define SPIKETRAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <glob.h>
#include <stdbool.h>

/**
 * @brief Defines a spike train
 */
typedef struct {
  size_t length; ///< length of spike train
  bool data[];    ///< the spike train
} spike_train_t;

/**
 * @brief Allocate memory for spike train
 * @param length Length of spike train
 * @return A spike train
 */
spike_train_t *spike_train_alloc(const size_t length);

/**
 * @brief Clears the spike train, i.e. sets all entries false.
 * @param spike_train
 */
void clear_spike_train(spike_train_t *spike_train);

/**
 * @brief Frees memory associated with spike spike_train
 * @param spike_train The spike spike_train
 */
void spike_train_free(spike_train_t *spike_train);

#ifdef __cplusplus
}
#endif

#endif // SPIKETRAIN_H
