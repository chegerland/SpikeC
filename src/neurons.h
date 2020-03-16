#ifndef NEURONS_H
#define NEURONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "spiketrain.h"
#include "timeframe.h"
#include <gsl/gsl_rng.h>

/**
 * @brief A struct storing the parameters of an integrate-and-fire model
 */
typedef struct {
  double mu;  ///< mean input current
  double D;   ///< diffusion coefficient
} if_params_t;

/**
 * @brief A struct storing the parameters of an integrate-and-fire model with an adaptation current.
 */
typedef struct {
  double mu;     ///< mean input current
  double D;      ///< diffusion coefficient
  double tau_a;  ///< adaptation time constant
  double Delta;  ///< kick size
} ifac_params_t;

/**
 * @brief Generates spike train of a leaky integrate-and-fire model.
 * @param [in] r Random number generator
 * @param [in] if_params Integrate-and-fire parameters
 * @param [in] time_frame Time frame
 * @param [out] spike_train The spike train
 */
void get_spike_train_lif(const gsl_rng *r, const if_params_t *if_params,
                         const time_frame_t *time_frame,
                         spike_train_t *spike_train);

/**
 * @brief Generates spike train of a leaky integrate-and-fire model subject to a signal.
 * @param [in] r Random number generator
 * @param [in] if_params Integrate-and-fire parameters
 * @param [in] signal Array containing signal.
 * @param [in] time_frame Time frame
 * @param [out] spike_train The spike train
 */
void get_spike_train_lif_signal(const gsl_rng *r, const if_params_t *if_params,
                                const double *signal,
                                const time_frame_t *time_frame,
                                spike_train_t *spike_train);

/**
 * @brief Calculates the trajectory of a LIF neuron, i.e. v(t).
 * @param r Random number generator
 * @param if_params Integrate-and-fire parameters
 * @param v Array containing the voltage values
 */
void get_trajectory_lif(const gsl_rng *r, const if_params_t * if_params, const time_frame_t * time_frame, double *v);

/**
 * @brief Generates spike train of a perfect integrate-and-fire model.
 * @param [in] r Random number generator
 * @param [in] if_params Integrate-and-fire parameters
 * @param [in] time_frame Time frame
 * @param [out] spike_train The spike train
 */
void get_spike_train_pif(const gsl_rng *r, const if_params_t *if_params,
                         const time_frame_t *time_frame,
                         spike_train_t *spike_train);

/**
 * @brief Generates spike train of a perfect integrate-and-fire model subject to a signal.
 * @param [in] r Random number generator
 * @param [in] if_params Integrate-and-fire parameters
 * @param [in] signal Array containing signal.
 * @param [in] time_frame Time frame
 * @param [out] spike_train The spike train
 */
void get_spike_train_pif_signal(const gsl_rng *r, const if_params_t *if_params,
                                const double *signal,
                                const time_frame_t *time_frame,
                                spike_train_t *spike_train);

/**
 * @brief Calculates the trajectory of a PIF neuron, i.e. v(t).
 * @param r Random number generator
 * @param if_params Integrate-and-fire parameters
 * @param v Array containing the voltage values
 */
void get_trajectory_pif(const gsl_rng *r, const if_params_t * if_params, const time_frame_t * time_frame, double *v);

/**
 * @brief Generates spike train of a leaky integrate-and-fire model with an adaptation current.
 * @param [in] r Random number generator
 * @param [in] ifac_params IFAC parameters
 * @param [in] time_frame Time frame
 * @param [out] spike_train The spike train
 */
void get_spike_train_lifac(const gsl_rng *r, const ifac_params_t *ifac_params,
                           const time_frame_t *time_frame,
                           spike_train_t *spike_train);

/**
 * @brief Generates spike train of a leaky integrate-and-fire model with an adaptation current.
 * @param [in] r Random number generator
 * @param [in] ifac_params IFAC parameters
 * @param [in] signal Array containing signal.
 * @param [in] time_frame Time frame
 * @param [out] spike_train The spike train
 */
void get_spike_train_lifac_signal(const gsl_rng *r,
                                  const ifac_params_t *ifac_params,
                                  const double *signal,
                                  const time_frame_t *time_frame,
                                  spike_train_t *spike_train);

/**
 * @brief Generates spike train of a perfect integrate-and-fire model with an adaptation current.
 * @param [in] r Random number generator
 * @param [in] ifac_params IFAC parameters
 * @param [in] time_frame Time frame
 * @param [out] spike_train The spike train
 */
void get_spike_train_pifac(const gsl_rng *r, const ifac_params_t *ifac_params,
                           const time_frame_t *time_frame,
                           spike_train_t *spike_train);

/**
 * @brief Generates spike train of a perfect integrate-and-fire model with an adaptation current.
 * @param [in] r Random number generator
 * @param [in] ifac_params IFAC parameters
 * @param [in] signal Array containing signal.
 * @param [in] time_frame Time frame
 * @param [out] spike_train The spike train
 */
void get_spike_train_pifac_signal(const gsl_rng *r,
                                  const ifac_params_t *ifac_params,
                                  const double *signal,
                                  const time_frame_t *time_frame,
                                  spike_train_t *spike_train);

#ifdef __cplusplus
}
#endif

#endif // NEURONS_H
