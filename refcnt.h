
#ifndef REFCNT_H
#define REFCNT_H

#include <stdatomic.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __STDC_NO_ATOMICS__
#error "No atomic"
#endif

typedef atomic_uint refcnt_t;

static inline void add_ref(refcnt_t *ref) { atomic_fetch_add(ref, 1); }

static inline bool del_ref(refcnt_t *ref) { return atomic_fetch_sub(ref, 1) == 1; }

#ifdef __cplusplus
}
#endif

#endif