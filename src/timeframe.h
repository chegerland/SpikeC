#ifndef TIMEFRAME_H
#define TIMEFRAME_H

#ifdef __cplusplus
extern "C" {
#endif

#include <glob.h>

/**
 * @brief Defines a time frame
 */
typedef struct {
  double t_0;    ///< start time
  double t_end;  ///< end time
  double dt;     ///< time step
  size_t N;      ///< number of steps
  double t[];    ///< array containing times
} time_frame_t;

/**
 * @brief Allocate memory for time frame
 * @param t_0 Start time
 * @param t_end End time
 * @param dt Time frame
 * @return A time frame
 */
time_frame_t * time_frame_alloc(double t_0, double t_end, double dt);

/**
 * @brief Free memory associated with time frame
 * @param time The time frame
 */
void time_frame_free(time_frame_t *time_frame);


#ifdef __cplusplus
}
#endif

#endif // TIMEFRAME_H
