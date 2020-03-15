#include "timeframe.h"
#include <assert.h>
#include <stdlib.h>

// allocate memory
time_frame_t *time_frame_alloc(const double t_0, const double t_end,
                             const double dt) {
  assert(t_end > t_0);
  assert(dt < (t_end - t_0));

  // length of time array
  int N = (int)((t_end - t_0) / dt);
  // allocate memory for time frame
  time_frame_t *time_frame = (time_frame_t *)malloc(
      sizeof(time_frame_t) + N * sizeof(double));

  // pass parameters
  time_frame->t_0 = t_0;
  time_frame->t_end = t_end;
  time_frame->dt = dt;
  time_frame->N = N;

  // initialize times
  for (int i = 0; i < time_frame->N; i++) {
    time_frame->t[i] = t_0 + i * dt;
  }

  return time_frame;
}

void time_frame_free(time_frame_t *time_frame) {
  if (time_frame != NULL) {
    free(time_frame);
  }
}
