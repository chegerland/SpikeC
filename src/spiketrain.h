#ifndef SPIKETRAIN_H
#define SPIKETRAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "timeframe.h"

// spike train type
typedef struct {
  double dt;           // time step
  size_t length;       // length of the spike train
  double *spike_array; // array containing the spikes
} SpikeTrain;

SpikeTrain *create_spike_train(const TimeFrame *time_frame);

void clear_spike_train(const SpikeTrain *spike_train);
void free_spike_train(SpikeTrain *spike_train);

#ifdef __cplusplus
}
#endif

#endif // SPIKETRAIN_H
