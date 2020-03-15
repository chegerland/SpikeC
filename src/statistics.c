#include "statistics.h"
#include <assert.h>
#include <stdlib.h>

// count number of spikes
int spike_count(const spike_train_t *spike_train) {
  int count = 0;

  // increase count for every spike in the spike train
  for (int i = 0; i < spike_train->length; i++) {
    if (spike_train->data[i] == true) {
      count++;
    }
  }

  return count;
}

// calculate spike times
int spike_times(double *times, const spike_train_t *spike_train,
                const time_frame_t *time_frame) {

  assert(spike_train->length == time_frame->N);

  // get the number of spikes
  int number_of_spikes = spike_count(spike_train);

  // give spike times array the right size
  times = (double *)realloc(times, sizeof(double) * number_of_spikes);

  // add corresponding time to spike times array
  int count = 0;
  for (int i = 0; i < spike_train->length; i++) {
    if (spike_train->data[i] == true) {
      times[count] = time_frame->t[i];
      count++;
    }
  }

  return count;
}

// add spike train to firing rate
void add_to_firing_rate(double *firing_rate, int N,
                        const spike_train_t *spike_train,
                        const time_frame_t *time_frame) {

  // add to firing rate
  for (int i = 0; i < spike_train->length; i++) {
    if (spike_train->data[i] == true) {
      firing_rate[i] += 1. / ((double)N * time_frame->dt);
    }
  }
}
