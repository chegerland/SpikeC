#ifndef TIMEFRAME_H
#define TIMEFRAME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "utils/ini.h"
#include <stdio.h>

//! A time frame structure
typedef struct {
  double t_0;   ///< start time
  double t_end; ///< end time
  double dt;    ///< time step
  int N;        ///< number of steps
  double *t;    ///< array containing times
} TimeFrame;

TimeFrame *create_time_frame(double t_0, double t_end, double dt);
TimeFrame *read_time_frame(ini_t *ini_file);

void free_time_frame(TimeFrame *time_frame);
void print_time_frame(FILE *fp, TimeFrame *time_frame);

#ifdef __cplusplus
}
#endif

#endif // TIMEFRAME_H
