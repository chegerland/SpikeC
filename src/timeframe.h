#ifndef TIMEFRAME_H
#define TIMEFRAME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ini/ini.h"

/**
 * @brief Defines a time frame
 */
typedef struct {
  double t_0;   ///< start time
  double t_end; ///< end time
  double dt;    ///< time step
  int N;     ///< number of steps
  double *t;    ///< array containing times
} TimeFrame;

/**
 * @brief Allocate memory for time frame
 * @param t_0 Start time
 * @param t_end End time
 * @param dt Time frame
 * @return A time frame
 */
TimeFrame *create_time_frame(double t_0, double t_end, double dt);

/**
 * @brief Creates time frame from given .ini file
 * @param ini_file Ini file object
 * @return A time frame
 */
TimeFrame *read_time_frame(ini_t *ini_file);

/**
 * @brief Free memory associated with time frame
 * @param time The time frame
 */
void free_time_frame(TimeFrame *time_frame);

#ifdef __cplusplus
}
#endif

#endif // TIMEFRAME_H
