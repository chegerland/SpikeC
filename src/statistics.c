#include <assert.h>
#include <fftw3.h>
#include <math.h>
#include <stdlib.h>

#include "statistics.h"

// calculate mean of given array
double mean(const double *values, const int N) {
  double mean = 0.0;
  for (int i = 0; i < N; i++) {
    mean += 1. / ((double)N) * values[i];
  }
  return mean;
}

// calculate standard deviation of given array
double standard_deviation(const double *values, const int N) {
  double mean_val = mean(values, N);
  double std = 0.0;

  for (int i = 0; i < N; i++) {
    std += 1. / ((double)N) * pow(values[i] - mean_val, 2);
  }

  return std;
}

// count number of spikes
int spike_count(const spike_train_t *spike_train) {
  int count = 0;

  // increase count for every spike in the spike train
  for (int i = 0; i < spike_train->length; i++) {
    if (spike_train->data[i] == true) {
      count++;
    }
  }

  return count;
}

// calculate spike times
int spike_times(const spike_train_t *spike_train,
                const time_frame_t *time_frame, double *times) {

  assert(spike_train->length == time_frame->N);

  // get the number of spikes
  int number_of_spikes = spike_count(spike_train);

  // give spike times array the right size
  times = (double *)realloc(times, sizeof(double) * number_of_spikes);

  // add corresponding time to spike times array
  int count = 0;
  for (int i = 0; i < spike_train->length; i++) {
    if (spike_train->data[i] == true) {
      times[count] = time_frame->t[i];
      count++;
    }
  }

  return count;
}

// add spike train to firing rate
void add_to_firing_rate(const spike_train_t *spike_train, const int N,
                        const time_frame_t *time_frame, double *firing_rate) {

  // add to firing rate
  for (int i = 0; i < spike_train->length; i++) {
    if (spike_train->data[i] == true) {
      firing_rate[i] += 1. / ((double)N * time_frame->dt);
    }
  }
}

// calculate cross spectrum
void cross_spectrum(double *input_signal, double *output_signal,
                    const time_frame_t *time_frame, fftw_complex *spectrum) {

  // length of the signals is N/2 + 1 because we perform real DFT
  int length = (int)time_frame->N / 2 + 1;

  // time step
  double dt = time_frame->dt;

  // fourier transform first signal
  fftw_plan p;
  fftw_complex *input_signal_fourier;
  input_signal_fourier =
      (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * length);
  p = fftw_plan_dft_r2c_1d(length, input_signal, input_signal_fourier,
                           FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);

  // fourier transform second signal
  fftw_plan p2;
  fftw_complex *output_signal_fourier;
  output_signal_fourier =
      (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * length);
  p2 = fftw_plan_dft_r2c_1d(length, output_signal, output_signal_fourier,
                            FFTW_ESTIMATE);
  fftw_execute(p2);
  fftw_destroy_plan(p2);

  // fill cross spectrum, S_xy = x(omega) * y^*(omega)
  // normalize appropriately
  double scale = dt * dt / (time_frame->t_end - time_frame->t_0);
  for (int i = 0; i < length; i++) {
    spectrum[i][0] =
        scale * (input_signal_fourier[i][0] * output_signal_fourier[i][0] +
                 input_signal_fourier[i][1] * output_signal_fourier[i][1]);
    spectrum[i][1] =
        scale * (input_signal_fourier[i][0] * output_signal_fourier[i][1] -
                 input_signal_fourier[i][1] * output_signal_fourier[i][0]);
  }

  // free memory
  fftw_free(input_signal_fourier);
  fftw_free(output_signal_fourier);
}

// calculate power spectrum
void power_spectrum(double *signal, const time_frame_t *time_frame,
                    double *spectrum) {
  // length of the signals is N/2 + 1 because we perform real DFT
  int length = (int)time_frame->N / 2 + 1;

  // time step
  double dt = time_frame->dt;

  // fourier transform first signal
  fftw_plan p;
  fftw_complex *signal_fourier;
  signal_fourier = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * length);
  p = fftw_plan_dft_r2c_1d(length, signal, signal_fourier, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);

  // calculate power spectrum and normalize appropriately!
  double scale = dt * dt / (time_frame->t_end - time_frame->t_0);
  for (int i = 0; i < length; i++) {
    spectrum[i] = scale * (signal_fourier[i][0] * signal_fourier[i][0] +
                           signal_fourier[i][1] * signal_fourier[i][1]);
  }

  // free memory
  fftw_free(signal_fourier);
}

// calculate susceptibility
void susceptibility(double *input_signal, double *output_signal,
                    const time_frame_t *time_frame, fftw_complex *suscept) {

  // length of the signals is N/2 + 1 because we perform real DFT
  int length = (int)time_frame->N / 2 + 1;

  // time step
  double dt = time_frame->dt;

  // fourier transform first signal
  fftw_plan p;
  fftw_complex *input_signal_fourier;
  input_signal_fourier =
      (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * length);
  p = fftw_plan_dft_r2c_1d(length, input_signal, input_signal_fourier,
                           FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);

  // fourier transform second signal
  fftw_plan p2;
  fftw_complex *output_signal_fourier;
  output_signal_fourier =
      (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * length);
  p2 = fftw_plan_dft_r2c_1d(length, output_signal, output_signal_fourier,
                            FFTW_ESTIMATE);
  fftw_execute(p2);
  fftw_destroy_plan(p2);

  // fill susceptibility and normalize appropriately
  double scale;
  for (int i = 0; i < length; i++) {
    scale = dt * dt /
            (input_signal_fourier[i][0] * input_signal_fourier[i][0] +
             input_signal_fourier[i][1] * input_signal_fourier[i][1]);
    suscept[i][0] =
        scale * (input_signal_fourier[i][0] * output_signal_fourier[i][0] +
                 input_signal_fourier[i][1] * output_signal_fourier[i][1]);
    suscept[i][1] =
        scale * (input_signal_fourier[i][0] * output_signal_fourier[i][1] -
                 input_signal_fourier[i][1] * output_signal_fourier[i][0]);
  }

  // free memory
  fftw_free(input_signal_fourier);
  fftw_free(output_signal_fourier);
}
