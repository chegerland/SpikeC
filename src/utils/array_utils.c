#include "array_utils.h"

// sets all values of a double array a of size length to zero
inline void clear_double_array(size_t length, double *a) {
  for (size_t i = 0; i < length; i++) {
    a[i] = 0.;
  }
}
