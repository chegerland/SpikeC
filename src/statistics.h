#ifndef STATISTICS_H
#define STATISTICS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "timeframe.h"
#include <fftw3.h>

double mean(size_t length, const double *array);
double variance(size_t length, const double *array);
double calculate_cv(size_t length, double *array);

int spike_count(size_t length, const double *spike_train);
int calculate_spike_times(const TimeFrame *time_frame,
                          const double *spike_train, double *spike_times);

void power_spectrum(const double *signal, const TimeFrame *time_frame,
                    double *spectrum, size_t norm);
void cross_spectrum(const double *first_signal, const double *second_signal,
                    const TimeFrame *time_frame, double complex *spectrum,
                    size_t norm);

void susceptibility_lin(const double complex *isf, const double *spike_train,
                        const TimeFrame *time_frame, double complex *suscept,
                        size_t norm);
void susceptibility_lin_nonlin(const double *signal, const double *spike_train,
                               const TimeFrame *time_frame,
                               double complex *suscept_lin,
                               double complex *suscept_nonlin, size_t norm);
void susceptibility_lin_nonlin_matrix(const double complex *isf, double alpha,
                                      const double *spike_train,
                                      const TimeFrame *time_frame,
                                      double complex *suscept_lin,
                                      double complex *suscept_nonlin,
                                      size_t norm);

#ifdef __cplusplus
}
#endif

#endif // STATISTICS_H
