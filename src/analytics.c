#include "analytics.h"

#include <gsl/gsl_integration.h>
#include <gsl/gsl_sf_erf.h>
#include <math.h>

double firing_rate_pif(if_params_t *pif_params) { return pif_params->mu; }

double lif_integrand(double x, void *params) {
  return exp(x * x) * gsl_sf_erfc(x);
}

// approximation of exp(x*x)*erfc(x) from Lether 1989
// (https://doi.org/10.1016/0022-4073(90)90134-R)
double lif_integrand_approx(double x, void *params) {
  double denom =
      x + sqrt(2.0 * (1.0 - (1.0 - 2.0 / M_PI) * exp(-x * sqrt(5.0 / 7.0))) +
               x * x);
  return 2.0 / (sqrt(M_PI) * denom);
}

double firing_rate_lif(if_params_t *lif_params) {

  // create workspace and variables
  gsl_integration_cquad_workspace *w =
      gsl_integration_cquad_workspace_alloc(1000);
  double result, error;

  gsl_function F;
  F.function = &lif_integrand_approx;

  double lower_bound = (lif_params->mu - 1.0) / sqrt(2.0 * lif_params->D);
  double upper_bound = (lif_params->mu) / sqrt(2.0 * lif_params->D);

  gsl_integration_cquad(&F, lower_bound, upper_bound, 0, 1e-13, w, &result,
                        &error, NULL);

  gsl_integration_cquad_workspace_free(w);

  result *= sqrt(M_PI);
  return 1.0 / result;
}
