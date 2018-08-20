
#include "minunit.h"
#include "string_slice.h"

const char *test_string_make_empty() {
  string_t *s = string_make_empty(16);
  mu_assert("error, s == null", s);
  mu_assert("error, s size != 0", string_size(s) == 0);
  string_del_ref(s);
  return 0;
}

const char *test_string_make_slice() {
  string_t *s = string_make_copy("Hello, world", 12);
  mu_assert("error, s == null", s);

  string_t *slice1 = string_make_slice(s, 0, string_size(s));
  mu_assert("error, slice1 == null", slice1);
  string_del_ref(slice1);

  string_t *slice2 = string_make_slice(s, 4, string_size(s) - 8);
  mu_assert("error, slice2 == null", slice2);
  string_del_ref(slice2);

  // slice3 is null
  string_t *slice3 = string_make_slice(s, 8, string_size(s) - 4);
  mu_assert("error, slice3 != null", !slice3);

  string_del_ref(s);
  return 0;
}

const char *test_string_make_copy_cstr() {
  string_t *s = string_make_copy_cstr("Hello, world");
  mu_assert("error, s == null", s);
  mu_assert("error, s is not 'Hello, world'", string_equals_cstr(s, "Hello, world"));
  string_del_ref(s);
  return 0;
}

const char *test_string_make_copy() {
  string_t *s = string_make_copy("Hello, world", 5);
  mu_assert("error, s == null", s);
  mu_assert("error, s is not Hello", string_equals_cstr(s, "Hello"));
  string_del_ref(s);
  return 0;
}

const char *test_string_append_buf() {
  bool result = false;
  string_t *s = string_make_empty(16);
  mu_assert("error, s == null", s);
  result = string_append_buf(s, "Hello, world", 5);
  mu_assert("error, string_append_buf failed", result);
  mu_assert("error, s is not Hello", string_equals_cstr(s, "Hello"));

  result = string_append_buf(s, "Hello, world", 12);
  mu_assert("error, string_append_buf failed", result);
  mu_assert("error, s is not 'HelloHello, world'",
            string_equals_cstr(s, "HelloHello, world"));
  string_del_ref(s);
  return 0;
}

const char *test_string_append_str() {
  bool result = false;
  string_t *s = string_make_empty(16);
  mu_assert("error, s == null", s);

  string_t *s1 = string_make_copy_cstr("Hello, world");
  result = string_append_str(s, s1);
  mu_assert("error, string_append_str failed", result);
  mu_assert("error, s not equals s1", string_equals(s, s1));

  result = string_append_str(s, s1);
  mu_assert("error, string_append_str failed", result);
  mu_assert("error, s not equals 'Hello, worldHello, world'",
            string_equals_cstr(s, "Hello, worldHello, world"));

  string_del_ref(s1);
  string_del_ref(s);
  return 0;
}

const char *test_string_append_cstr() {
  bool result = false;
  string_t *s = string_make_empty(16);
  mu_assert("error, s == null", s);

  result = string_append_cstr(s, "Hello, world");
  mu_assert("error, string_append_cstr failed", result);
  mu_assert("error, s is not 'Hello, world'",
            string_equals_cstr(s, "Hello, world"));

  result = string_append_cstr(s, "Hello, world");
  mu_assert("error, string_append_cstr failed", result);
  mu_assert("error, s is not 'Hello, worldHello, world'",
            string_equals_cstr(s, "Hello, worldHello, world"));

  string_del_ref(s);
  return 0;
}

const char *test_string_equals_cstr() {
  string_t *s = string_make_copy_cstr("Hello");
  mu_assert("s not equals Hello", string_equals_cstr(s, "Hello"));
  mu_assert("s equals hello", !string_equals_cstr(s, "hello"));
  string_del_ref(s);
  return 0;
}

const char *test_string_equals() {
  string_t *s = string_make_copy_cstr("Hello");
  string_t *s2 = string_make_copy_cstr("Hello");
  mu_assert("s not equals s2", string_equals(s, s2));

  string_t *s3 = string_make_copy_cstr("hello");
  mu_assert("s equals s3", !string_equals(s, s3));

  string_del_ref(s);
  string_del_ref(s2);
  string_del_ref(s3);
  return 0;
}

const char *test_string_equals_ignorecase() {
  string_t *s = string_make_copy_cstr("Hello");
  string_t *s2 = string_make_copy_cstr("hello");
  mu_assert("s not equals ignorecase s2", string_equals_ignorecase(s, s2));
  string_t *s3 = string_make_copy_cstr("hello1");
  mu_assert("s equals ignorecase s3", !string_equals_ignorecase(s, s3));

  string_del_ref(s);
  string_del_ref(s2);
  return 0;
}

const char *test_string_printf() {
  string_t *s = string_make_empty(16);
  string_printf(s, "%d", 1);
  mu_assert("s is 1", string_equals_cstr(s, "1"));

  string_printf(s, "Hello hello hello %s", "world");
  mu_assert("s is 1", string_equals_cstr(s, "Hello hello hello world"));
  return 0;
}

const char *all_tests() {
  mu_run_test(test_string_make_empty);
  mu_run_test(test_string_make_slice);
  mu_run_test(test_string_make_copy_cstr);
  mu_run_test(test_string_make_copy);
  mu_run_test(test_string_append_buf);
  mu_run_test(test_string_append_str);
  mu_run_test(test_string_append_cstr);
  mu_run_test(test_string_equals_cstr);
  mu_run_test(test_string_equals);
  mu_run_test(test_string_equals_ignorecase);
  mu_run_test(test_string_printf);
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