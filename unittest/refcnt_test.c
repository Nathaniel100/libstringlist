
#include "refcnt.h"
#include "minunit.h"

const char *test_addref() {
  refcnt_t ref = 0;
  add_ref(&ref);
  mu_assert("Ref equals 1 after add_ref", ref == 1);

  add_ref(&ref);
  mu_assert("Ref equals 2 after add_ref twice", ref == 2);
  return 0;
}

const char *test_delref() {
  refcnt_t ref = 0;
  add_ref(&ref);
  add_ref(&ref);

  mu_assert("Del ref returns false", !del_ref(&ref));
  mu_assert("Del ref returns true", del_ref(&ref));
  mu_assert("Ref equals 0", ref == 0);
  return 0;
}

const char *all_tests() {
  mu_run_test(test_addref);
  mu_run_test(test_delref);
  return NULL;
}

int tests_run = 0;
int main(int argc, char **argv) {
  const char *failed = all_tests();
  if (!failed) {
    printf(GRN "PASSED\n" RESET);
  }
  printf("Tests run: %d\n", tests_run);
  return 0;
}
