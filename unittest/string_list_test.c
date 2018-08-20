
#include "string_list.h"
#include "minunit.h"
#include <string.h>

const char *test_string_node_make_empty() {
  string_node_t *node = string_node_make_empty();
  mu_assert("node == null", node);
  string_node_free(node);
  return 0;
}

const char *test_string_node_make() {
  string_node_t *node = string_node_make(string_make_copy_cstr("Hello"));
  mu_assert("node == null", node);
  mu_assert("node str is not Hello", string_equals_cstr(node->str, "Hello"));
  string_node_free(node);
  return 0;
}

const char *test_string_list_make() {
  string_list_t *list = string_list_make();
  mu_assert("list == null", list);
  mu_assert("list not empty", string_list_empty(list));
  string_list_free(list);
  return 0;
}

// World -> Hello -> NULL
static string_list_t *make_test_list() {
  string_list_t *list = string_list_make();
  string_node_t *node = string_node_make(string_make_copy_cstr("Hello"));
  string_node_t *node2 = string_node_make(string_make_copy_cstr("World"));
  string_list_insert_before_head(list, node);
  string_list_insert_before_head(list, node2);
  return list;
}

static void print_list(string_list_t *list) {
  char buffer[1024] = {0};
  string_node_t *p = list->head;
  while(p) {
    memcpy(buffer, string_data(p->str), string_size(p->str));
    printf("%s\n", buffer);
    p = p->next;
  }
}

const char *test_string_list_insert_before_head() {
  string_list_t *list = string_list_make();
  mu_assert("list == null", list);
  string_node_t *node = string_node_make(string_make_copy_cstr("Hello"));
  mu_assert("node == null", node);
  string_list_insert_before_head(list, node);
  mu_assert("list is empty", !string_list_empty(list));
  mu_assert("list head str is not Hello",
            string_equals_cstr(list->head->str, "Hello"));

  string_node_t *node2 = string_node_make(string_make_copy_cstr("World"));
  mu_assert("node2 == null", node2);
  string_list_insert_before_head(list, node2);
  mu_assert("list head str is not World",
            string_equals_cstr(list->head->str, "World"));

  string_list_free(list);
  return 0;
}

const char *test_string_list_insert_after_head() {
  string_list_t *list = string_list_make();
  mu_assert("list == null", list);
  string_node_t *node = string_node_make(string_make_copy_cstr("Hello"));
  mu_assert("node == null", node);
  string_list_insert_after_head(list, node);
  mu_assert("list is empty", !string_list_empty(list));
  mu_assert("list head str is not Hello",
            string_equals_cstr(list->head->str, "Hello"));

  string_node_t *node2 = string_node_make(string_make_copy_cstr("World"));
  mu_assert("node2 == null", node2);
  string_list_insert_after_head(list, node2);
  mu_assert("list head str is not Hello",
            string_equals_cstr(list->head->str, "Hello"));
  mu_assert("node->next not node2", node->next == node2);

  string_list_free(list);
  return 0;
}

const char *test_string_list_find_cstr() {
  string_list_t *list = make_test_list();
  mu_assert("list == null", list);

  string_node_t *node = string_list_find_cstr(list, "Hello");
  mu_assert("Hello not found", node);

  string_node_t *node2 = string_list_find_cstr(list, "Hell");
  mu_assert("Hell found", !node2);

  string_list_free(list);
  return 0;
}

const char *test_string_list_find() {
  string_list_t *list = make_test_list();
  mu_assert("list == null", list);
  string_t *string_hello = string_make_copy("Hello", 5);
  string_t *string_hell = string_make_copy("Hell", 4);

  string_node_t *node = string_list_find(list, string_hello);
  mu_assert("Hello not found", node);

  string_node_t *node2 = string_list_find(list, string_hell);
  mu_assert("Hell found", !node2);

  string_del_ref(string_hello);
  string_del_ref(string_hell);
  string_list_free(list);
  return 0;
}

const char *test_string_list_remove_head() {
  string_list_t *list = make_test_list();
  mu_assert("list is null", list);

  string_node_t *node = string_list_remove_head(list);
  mu_assert("First removed head is World", string_equals_cstr(node->str, "World"));
  string_node_t *node2 = string_list_remove_head(list);
  mu_assert("Second removed head is Hello", string_equals_cstr(node2->str, "Hello"));

  mu_assert("list not empty", string_list_empty(list));

  string_node_free(node);
  string_node_free(node2);
  return 0;
}

const char *test_string_list_remove() {
  string_list_t *list = make_test_list();
  mu_assert("list is null", list);

  string_node_t *node = string_list_find_cstr(list, "Hello");
  mu_assert("Hello not found", node);
  string_node_t *node2 = string_list_find_cstr(list, "World");
  mu_assert("World not found", node2);

  string_list_remove_node(list, node);
  mu_assert("Hello found", !string_list_find_cstr(list, "Hello"));
  string_list_remove_node(list, node2);
  mu_assert("World found", !string_list_find_cstr(list, "World"));

  mu_assert("list not empty", string_list_empty(list));

  string_node_free(node);
  string_node_free(node2);
  return 0;
}

const char *all_tests() {
  mu_run_test(test_string_node_make_empty);
  mu_run_test(test_string_node_make);
  mu_run_test(test_string_list_make);
  mu_run_test(test_string_list_insert_before_head);
  mu_run_test(test_string_list_insert_after_head);
  mu_run_test(test_string_list_find_cstr);
  mu_run_test(test_string_list_find);
  mu_run_test(test_string_list_remove_head);
  mu_run_test(test_string_list_remove);
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