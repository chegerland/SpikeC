#ifndef STATISTICS_H
#define STATISTICS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "timeframe.h"
#include <fftw3.h>

double mean(int length, const double *array);

void susceptibility_lin(const double complex *isf, double *spike_train,
                        const TimeFrame *time_frame, double complex *suscept,
                        size_t norm);

void susceptibility_lin_nonlin(const double complex *isf, double alpha,
                               const double *spike_train,
                               const TimeFrame *time_frame,
                               double complex *suscept_lin,
                               double complex *suscept_nonlin, size_t norm);

void susceptibility_lin_nonlin_matrix(const double complex *isf, double alpha,
                                      const double *spike_train,
                                      const TimeFrame *time_frame,
                                      double complex *suscept_lin,
                                      double complex **suscept_nonlin,
                                      size_t norm);

#ifdef __cplusplus
}
#endif

#endif // STATISTICS_H
