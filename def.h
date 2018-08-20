#ifndef DEF_H
#define DEF_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline uint32_t power2(uint32_t v) {
  v |= (v >> 16);
  v |= (v >> 8);
  v |= (v >> 4);
  v |= (v >> 2);
  v |= (v >> 1);
  v += 1;
  return v;
}

static inline uint32_t max(uint32_t x, uint32_t y) {
  return x ^ ((x ^ y) & -(x < y));
}

static inline uint32_t min(uint32_t x, uint32_t y) {
  return y ^ ((x ^ y) & -(x < y));
}



#ifdef __cplusplus
}
#endif

#endif