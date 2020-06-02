#ifndef TIMEFRAME_H
#define TIMEFRAME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "utils/ini.h"
#include <stdio.h>

/**
 * @brief Implements a time frame.
 *
 * This struct represents the discretized time frame, with a start and end time,
 * a time step and of course the discrete times themselves in the form of an
 * array.
 */
typedef struct {
  double t_0;   ///< start time
  double t_end; ///< end time
  double dt;    ///< time step
  size_t N;     ///< number of steps
  double *t;    ///< array containing times
} TimeFrame;

/**
 * @brief Create a time frame from parameters.
 * @param t_0 Start time
 * @param t_end End time
 * @param dt Time step
 * @return A time frame
 */
TimeFrame *create_time_frame(double t_0, double t_end, double dt);

/**
 * @brief Creates time frame from given .ini file.
 * @param ini_file Ini file object
 * @return A time frame
 */
TimeFrame *read_time_frame(ini_t *ini_file);

/**
 * @brief Free memory associated with time frame.
 * @param time The time frame
 */
void free_time_frame(TimeFrame *time_frame);

/**
 * @brief Prints time frame parameters to stream.
 * @param stream Pointer to stream.
 * @param time_frame The time frame
 */
void print_time_frame(FILE *stream, const TimeFrame *time_frame);

#ifdef __cplusplus
}
#endif

#endif // TIMEFRAME_H
