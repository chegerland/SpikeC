#ifndef ANALYTICS_H
#define ANALYTICS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "neurons.h"

// formulae for firing rates
double firing_rate_pif(if_params_t *pif_params);
double firing_rate_lif(if_params_t *lif_params);


#ifdef __cplusplus
}
#endif

#endif // ANALYTICS_H
