#ifndef TIMEFRAME_H
#define TIMEFRAME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "utils/ini.h"
#include <stdio.h>

// time frame type
typedef struct {
  double t_0;
  double t_end;
  double dt;
  size_t N;
  double *t;
} TimeFrame;

// initializers
TimeFrame *create_time_frame(double t_0, double t_end, double dt);
TimeFrame *read_time_frame(ini_t *ini_file);

void free_time_frame(TimeFrame *time_frame);
void print_time_frame(FILE *stream, const TimeFrame *time_frame);

#ifdef __cplusplus
}
#endif

#endif // TIMEFRAME_H
