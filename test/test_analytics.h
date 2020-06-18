#ifndef TEST_ANALYTICS_H
#define TEST_ANALYTICS_H

#include "../src/spike.h"
#include "unittest.h"
#include <stdio.h>

static char *test_firing_rate_lif() {

  if_params_t lif_params = {3.5, 1e-3};

//  mu_assert("LIF firing rate is calculated correctly",
//            firing_rate_lif(&lif_params) == 2.4);

  printf("%lf\n", firing_rate_lif(&lif_params));

  return 0;
}

#endif // TEST_ANALYTICS_H
