#include "timeframe.h"
#include <assert.h>
#include <stdlib.h>

#include "math.h"

/**
 * @brief Allocate memory for time frame
 * @param t_0 Start time
 * @param t_end End time
 * @param dt Time frame
 * @return A time frame
 */
TimeFrame *create_time_frame(const double t_0, const double t_end,
                             const double dt) {
  assert(t_end > t_0);
  assert(dt < (t_end - t_0));

  // length of time array
  int N = (int)((t_end - t_0) / dt);

  // allocate memory for time frame
  TimeFrame *time_frame = (TimeFrame *)calloc(1, sizeof(TimeFrame));

  // pass parameters
  time_frame->t_0 = t_0;
  time_frame->t_end = t_end;
  time_frame->dt = dt;
  time_frame->N = N;

  // allocate memory for times
  time_frame->t = (double *)calloc(N, sizeof(double));

  // initialize times
  for (int i = 0; i < time_frame->N; i++) {
    time_frame->t[i] = t_0 + i * dt;
  }

  return time_frame;
}

/**
 * @brief Creates time frame from given .ini file
 * @param ini_file Ini file object
 * @return A time frame
 */
TimeFrame *read_time_frame(ini_t *ini_file) {
  TimeFrame *time_frame = (TimeFrame *)calloc(1, sizeof(TimeFrame));

  // read parameters from ini file
  double t_0 = NAN, t_end = NAN, dt = NAN;
  ini_sget(ini_file, "TimeFrame", "t_0", "%lf", &t_0);
  ini_sget(ini_file, "TimeFrame", "t_end", "%lf", &t_end);
  ini_sget(ini_file, "TimeFrame", "dt", "%lf", &dt);

  // length of time array
  int N = (int)((t_end - t_0) / dt);

  // pass parameters
  time_frame->t_0 = t_0;
  time_frame->t_end = t_end;
  time_frame->dt = dt;
  time_frame->N = N;

  // allocate memory for times
  time_frame->t = (double *)calloc(N, sizeof(double));

  // initialize times
  for (int i = 0; i < time_frame->N; i++) {
    time_frame->t[i] = t_0 + i * dt;
  }

  return time_frame;
}

/**
 * @brief Prints time frame parameters to file (or stderr)
 * @param fp Pointer to file (can be stderr)
 * @param time_frame The time frame
 */
void print_time_frame(FILE *fp, TimeFrame *time_frame) {
  fprintf(fp,
          "# TimeFrame\n"
          "#\n"
          "# t_0 = %lf\n"
          "# t_end = %lf\n"
          "# dt = %lf\n",
          time_frame->t_0, time_frame->t_end, time_frame->dt);
}

/**
 * @brief Free memory associated with time frame
 * @param time The time frame
 */
void free_time_frame(TimeFrame *time_frame) {
  if (time_frame != NULL) {
    free(time_frame->t);
    free(time_frame);
  }
}
