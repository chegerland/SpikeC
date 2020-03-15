#include "spiketrain.h"
#include <assert.h>
#include <stdlib.h>

// allocate memory for spike train
spike_train_t *spike_train_alloc(const size_t length) {

  assert(length > 0);

  // allocate memory for spike train
  spike_train_t *spike_train =
      (spike_train_t *)malloc(sizeof(spike_train_t) + length * sizeof(bool));
  spike_train->length = length;

  clear_spike_train(spike_train);

  return spike_train;
}

void clear_spike_train(spike_train_t *spike_train) {
  for (int i = 0; i < spike_train->length; i++) {
    spike_train->data[i] = false;
  }
}

void spike_train_free(spike_train_t *spike_train) {
  if (spike_train != NULL) {
    free(spike_train);
  }
}
