#include "../src/signals.h"
#include "../src/timeframe.h"
#include <complex.h>
#include <fftw3.h>
#include <math.h>

gsl_rng *rng;

int main(int argc, char *argv[]) {

  // parameters
  const double t_0 = 0.0;
  const double t_end = 500.0;
  const double dt = 1e-2;

  const double alpha = 0.035;
  const double f_low = 0.;
  const double f_high = 1. / (2. * dt);

  // setup rng
  const gsl_rng_type *type = gsl_rng_mt19937;
  gsl_rng_env_setup();
  rng = gsl_rng_alloc(type);

  // define time frame and spike train
  TimeFrame *time_frame = create_time_frame(t_0, t_end, dt);

  // define signal and its frequencies
  double *signal = (double *)calloc(time_frame->N, sizeof(double));
  double complex *frequencies =
      (double complex *)calloc(time_frame->N / 2 + 1, sizeof(double complex));

  band_limited_white_noise(rng, alpha, f_low, f_high, time_frame, signal,
                           frequencies);

  double T = time_frame->t_end - time_frame->t_0;
  printf("-----------\n");
  for (int i = 0; i < time_frame->N / 2; i++) {
    //printf("%f\n",
    //       (pow(creal(frequencies[i]), 2) + pow(cimag(frequencies[i]), 2)) / T);
    printf("%f\n",
           pow(cabs(frequencies[i]),2)/T);
  }
  printf("-----------\n");

  double mean = 0.;
  for (int i = 0; i < time_frame->N; i++) {
    mean += 1./((double) time_frame->N) * signal[i];
  }

  double std = 0.;
  for (int i = 0; i < time_frame->N; i++) {
    std += (signal[i] - mean)*(signal[i] - mean);
  }

  printf("pow(cabs(isf[i]),2) = %f\n", pow(cabs(frequencies[3]),2));
  printf("pow(cabs(isf[i]),2)/T = %f\n", pow(cabs(frequencies[3]),2)/T);
  printf("var (num) = %f\n", std/((double) time_frame->N));
  printf("var (ana) = %f\n", 2. * alpha /time_frame->dt);


  free(signal);
  free(frequencies);
}
