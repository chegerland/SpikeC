#include "timeframe.h"
#include <assert.h>
#include <stdlib.h>

#include "math.h"

// creates a time frame from parameters
TimeFrame *create_time_frame(const double t_0, const double t_end,
                             const double dt) {
  assert(t_end > t_0);
  assert(dt < (t_end - t_0));

  // length of time array
  size_t N = (t_end - t_0) / dt + 1;

  // allocate memory for time frame
  TimeFrame *time_frame = malloc(sizeof(TimeFrame));

  // pass parameters
  time_frame->t_0 = t_0;
  time_frame->t_end = t_end;
  time_frame->dt = dt;
  time_frame->N = N;

  // allocate memory for times
  time_frame->t = malloc(N * sizeof(double));

  // initialize times
  for (size_t i = 0; i < time_frame->N; i++) {
    time_frame->t[i] = t_0 + i * dt;
  }

  return time_frame;
}

// creates a time frame from ini file
TimeFrame *read_time_frame(ini_t *ini_file) {
  TimeFrame *time_frame = malloc(sizeof(TimeFrame));

  // read parameters from ini file
  double t_0 = NAN, t_end = NAN, dt = NAN;
  ini_sget(ini_file, "TimeFrame", "t_0", "%lf", &t_0);
  ini_sget(ini_file, "TimeFrame", "t_end", "%lf", &t_end);
  ini_sget(ini_file, "TimeFrame", "dt", "%lf", &dt);

  assert(t_end > t_0);
  assert(dt < (t_end - t_0));

  // length of time array
  size_t N = (t_end - t_0) / dt + 1;

  // pass parameters
  time_frame->t_0 = t_0;
  time_frame->t_end = t_end;
  time_frame->dt = dt;
  time_frame->N = N;

  // allocate memory for times
  time_frame->t = malloc(N * sizeof(double));

  // initialize times
  for (size_t i = 0; i < time_frame->N; i++) {
    time_frame->t[i] = t_0 + i * dt;
  }

  return time_frame;
}

// prints information of the time frame to stream
void print_time_frame(FILE *stream, const TimeFrame *time_frame) {
  fprintf(stream,
          "# [TimeFrame]\n"
          "# t_0 = %lf\n"
          "# t_end = %lf\n"
          "# dt = %lf\n",
          time_frame->t_0, time_frame->t_end, time_frame->dt);
}

// frees memory associated with the time frame
void free_time_frame(TimeFrame *time_frame) {
  if (time_frame != NULL) {
    free(time_frame->t);
    free(time_frame);
  }
}
