#include "neurons.h"
#include <gsl/gsl_randist.h>
#include <math.h>

void get_spike_train_lif(const gsl_rng *r, const if_params_t *if_params,
                         const time_frame_t *time_frame,
                         spike_train_t *spike_train) {
  // initial values
  double v = 0.;

  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += (if_params->mu - v) * dt +
         sqrt(2.0 * if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    if (v > 1.0) {
      v = 0.;
      spike_train->data[i] = true;
    }
  }
}

void get_spike_train_lif_signal(const gsl_rng *r, const if_params_t *if_params,
                                const double *signal,
                                const time_frame_t *time_frame,
                                spike_train_t *spike_train) {
  // initial values
  double v = 0.;

  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += (if_params->mu - v + signal[i]) * dt +
         sqrt(2.0 * if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    if (v > 1.0) {
      v = 0.;
      spike_train->data[i] = true;
    }
  }
}

void get_trajectory_lif(const gsl_rng *r, const if_params_t *if_params,
                        const time_frame_t *time_frame, double *v){

  // initial values
  v[0] = 0.;

  double dt = time_frame->dt;

  for (int i = 1; i < time_frame->N; i++) {
    v[i] = v[i-1] + (if_params->mu - v[i-1]) * dt +
         sqrt(2.0 * if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    if (v[i] > 1.0) {
      v[i] = 0.;
    }
  }
}

void get_spike_train_pif(const gsl_rng *r, const if_params_t *if_params,
                         const time_frame_t *time_frame,
                         spike_train_t *spike_train) {
  // initial values
  double v = 0.;

  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += if_params->mu * dt +
         sqrt(2.0 * if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    if (v > 1.0) {
      v = 0.;
      spike_train->data[i] = true;
    }
  }
}

void get_spike_train_pif_signal(const gsl_rng *r, const if_params_t *if_params,
                                const double *signal,
                                const time_frame_t *time_frame,
                                spike_train_t *spike_train) {
  // initial values
  double v = 0.;

  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += (if_params->mu + signal[i]) * dt +
         sqrt(2.0 * if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    if (v > 1.0) {
      v = 0.;
      spike_train->data[i] = true;
    }
  }
}


void get_trajectory_pif(const gsl_rng *r, const if_params_t *if_params,
                        const time_frame_t *time_frame, double *v){

  // initial values
  v[0] = 0.;

  double dt = time_frame->dt;

  for (int i = 1; i < time_frame->N; i++) {
    v[i] = v[i-1] + if_params->mu * dt +
           sqrt(2.0 * if_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    if (v[i] > 1.0) {
      v[i] = 0.;
    }
  }
}

void get_spike_train_lifac(const gsl_rng *r, const ifac_params_t *ifac_params,
                           const time_frame_t *time_frame,
                           spike_train_t *spike_train) {
  // initial values
  double v = 0.;
  double a = 0.;

  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += (ifac_params->mu - v - a) * dt +
         sqrt(2.0 * ifac_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    a += -1. / ifac_params->tau_a * a * dt;
    if (v > 1.0) {
      v = 0.;
      a += ifac_params->Delta;
      spike_train->data[i] = true;
    }
  }
}

void get_spike_train_lifac_signal(const gsl_rng *r,
                                  const ifac_params_t *ifac_params,
                                  const double *signal,
                                  const time_frame_t *time_frame,
                                  spike_train_t *spike_train) {
  // initial values
  double v = 0.;
  double a = 0.;

  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += (ifac_params->mu - v - a + signal[i]) * dt +
         sqrt(2.0 * ifac_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    a += -1. / ifac_params->tau_a * a * dt;
    if (v > 1.0) {
      v = 0.;
      a += ifac_params->Delta;
      spike_train->data[i] = true;
    }
  }
}

void get_spike_train_pifac(const gsl_rng *r, const ifac_params_t *ifac_params,
                           const time_frame_t *time_frame,
                           spike_train_t *spike_train) {
  // initial values
  double v = 0.;
  double a = 0.;

  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += (ifac_params->mu - a) * dt +
         sqrt(2.0 * ifac_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    a += -1. / ifac_params->tau_a * a * dt;
    if (v > 1.0) {
      v = 0.;
      a += ifac_params->Delta;
      spike_train->data[i] = true;
    }
  }
}

void get_spike_train_pifac_signal(const gsl_rng *r,
                                  const ifac_params_t *ifac_params,
                                  const double *signal,
                                  const time_frame_t *time_frame,
                                  spike_train_t *spike_train) {
  // initial values
  double v = 0.;
  double a = 0.;

  double dt = time_frame->dt;

  for (int i = 0; i < time_frame->N; i++) {
    v += (ifac_params->mu - a + signal[i]) * dt +
         sqrt(2.0 * ifac_params->D) * gsl_ran_gaussian(r, sqrt(dt));
    a += -1. / ifac_params->tau_a * a * dt;
    if (v > 1.0) {
      v = 0.;
      a += ifac_params->Delta;
      spike_train->data[i] = true;
    }
  }
}
