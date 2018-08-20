
#ifndef UNITTEST_MINUNIT_H
#define UNITTEST_MINUNIT_H

#include <stdbool.h>
#include <stdio.h>

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

#define mu_fail(message)                                                    \
  do {                                                                      \
    fprintf(stderr, RED "[%s:%d] %s\n" RESET, __FILE__, __LINE__, message); \
  } while (0)

#define mu_assert(message, test) \
  do {                           \
    if (!(test)) {               \
      mu_fail(message);          \
      return message;            \
    }                            \
  } while (0)

#define mu_run_test(test)         \
  do {                            \
    const char *message = test(); \
    tests_run++;                  \
    if (message) return message;  \
  } while (0)

extern int tests_run;

#endif