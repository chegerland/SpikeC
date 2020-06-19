#ifndef STATISTICS_H
#define STATISTICS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "timeframe.h"

double mean(size_t length, const double *array);
double variance(size_t length, const double *array);
double calculate_cv(size_t length, double *array);

size_t spike_count(size_t length, const double *spike_train);
size_t calculate_isi(const TimeFrame *time_frame,
                          const double *spike_train, double *spike_times);

void power_spectrum(const double *signal, const TimeFrame *time_frame,
                    double *spectrum, const size_t norm);
void cross_spectrum(const double *first_signal, const double *second_signal,
                    const TimeFrame *time_frame, double complex *spectrum,
                    const size_t norm);

void susceptibility_lin(const double *input_signal, const double *output_signal,
                        const TimeFrame *time_frame, double complex *suscept,
                        const size_t norm);
void susceptibility_lin_nonlin(const double *input_signal, const double *output_signal,
                               const TimeFrame *time_frame,
                               double complex *suscept_lin,
                               double complex *suscept_nonlin, const size_t norm);
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
