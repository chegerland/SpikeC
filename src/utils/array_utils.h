#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

// sets all values of a double array a of size length to zero
inline void clear_double_array(size_t length, double *a) {
  for (size_t i = 0; i < length; i++) {
    a[i] = 0.;
  }
}

#ifdef __cplusplus
}
#endif

#endif // ARRAY_UTILS_H
