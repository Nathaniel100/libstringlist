#include "def.h"
#include "minunit.h"

const char *test_power2() {
  mu_assert("power2(1) != 2", power2(1) == 2);
  mu_assert("power2(2) != 4", power2(2) == 4);
  mu_assert("power2(7) != 8", power2(7) == 8);
  mu_assert("power2(8) != 16", power2(8) == 16);
  mu_assert("power2(9) != 16", power2(9) == 16);
  return 0;
}

const char *test_max() {
  mu_assert("max(1, 2) == 2", max(1, 2) == 2);
  mu_assert("max(2, 2) == 2", max(2, 2) == 2);
  mu_assert("max(2, 1) == 2", max(2, 1) == 2);
  return 0;
}

const char *test_min() {
  mu_assert("min(1, 2) == 1", min(1, 2) == 1);
  mu_assert("min(1, 1) == 1", min(1, 1) == 1);
  mu_assert("min(2, 1) == 1", min(2, 1) == 1);
  return 0;
}

const char *all_tests() {
  mu_run_test(test_power2);
  mu_run_test(test_max);
  mu_run_test(test_min);
  return 0;
}

int tests_run;
int main() {
  const char *failed = all_tests();
  if (!failed) {
    printf(GRN "PASSED\n" RESET);
  }
  printf("Tests run: %d\n", tests_run);
  return 0;
}