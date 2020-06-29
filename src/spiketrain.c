#include "spiketrain.h"
#include "utils/array_utils.h"

#include <stdlib.h>

// creates a spike train from a given time frame
SpikeTrain *create_spike_train(const TimeFrame *time_frame) {
  // allocate memory for spike train
  SpikeTrain *spike_train = malloc(sizeof(SpikeTrain));

  // pass parameters
  spike_train->dt = time_frame->dt;
  spike_train->length = time_frame->N;
  spike_train->spike_array = malloc(spike_train->length * sizeof(double));
  clear_spike_train(spike_train);

  return spike_train;
}

// sets all values of the spike array to zero
inline void clear_spike_train(const SpikeTrain *spike_train) {
  clear_double_array(spike_train->length, spike_train->spike_array);
}

// frees memory associated with the spike train
void free_spike_train(SpikeTrain *spike_train) {
  if (spike_train != NULL) {
    free(spike_train->spike_array);
    free(spike_train);
  }
}
