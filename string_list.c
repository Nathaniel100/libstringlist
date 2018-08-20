#include "string_list.h"
#include <stdlib.h>

string_node_t *string_node_make_empty() {
  string_t *s = string_make_empty(16);
  if (!s) {
    return NULL;
  }
  string_node_t *node = (string_node_t *) malloc(sizeof(string_node_t));
  if (!node) {
    string_del_ref(s);
    return NULL;
  }
  node->str = s;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

string_node_t *string_node_make(string_t *str) {
  string_node_t *node = (string_node_t *) malloc(sizeof(string_node_t));
  if (!node) {
    return NULL;
  }
  node->str = str;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

static void string_node_remove(string_node_t *node) {
  node->prev = NULL;
  node->next = NULL;
}

static void string_node_update(string_node_t *node) {
  if (node->prev) {
    node->prev->next = node;
  }
  if (node->next) {
    node->next->prev = node;
  }
}


void string_node_free(string_node_t *node) {
  if (node->str) {
    string_del_ref(node->str);
  }
  node->str = NULL;
  string_node_remove(node);
  free(node);
}

string_list_t *string_list_make() {
  string_list_t *list = (string_list_t *) malloc(sizeof(string_list_t));
  if (!list) {
    return NULL;
  }
  list->head = NULL;
  return list;
}

void string_list_free(string_list_t *list) {
  string_node_t *p = list->head;
  while (p) {
    string_node_free(p);
    p = p->next;
  }
  free(list);
}

bool string_list_empty(const string_list_t *list) { return list->head == NULL; }

string_node_t *string_list_insert_before_head(string_list_t *list,
                                              string_node_t *node) {
  string_node_remove(node);
  if (list->head) {
    node->prev = list->head->prev;
  }
  node->next = list->head;
  string_node_update(node);
  list->head = node;
  return node;
}

string_node_t *string_list_insert_after_head(string_list_t *list,
                                             string_node_t *node) {
  string_node_remove(node);
  node->prev = list->head;
  if (list->head) {
    node->next = list->head->next;
  }
  string_node_update(node);
  if (!list->head) {
    list->head = node;
  }
  return node;
}

string_node_t *string_list_insert_before(string_list_t *list,
                                         string_node_t *base,
                                         string_node_t *node) {
  string_node_remove(node);
  if (base) {
    node->prev = base->prev;
  }
  node->next = base;
  string_node_update(node);
  if (base == list->head) {
    list->head = node;
  }
  return node;
}

string_node_t *string_list_insert_after(string_list_t *list,
                                        string_node_t *base,
                                        string_node_t *node) {
  string_node_remove(node);
  node->prev = base;
  if (base) {
    node->next = base->next;
  }
  string_node_update(node);
  if (!list->head) {
    list->head = node;
  }
  return node;
}

string_node_t *string_list_find(string_list_t *list, const string_t *str) {
  string_node_t *p = list->head;
  while (p) {
    if (string_equals(p->str, str)) {
      break;
    }
    p = p->next;
  }
  return p;
}

string_node_t *string_list_find_cstr(string_list_t *list, const char *str) {
  string_node_t *p = list->head;
  while (p) {
    if (string_equals_cstr(p->str, str)) {
      break;
    }
    p = p->next;
  }
  return p;
}

string_node_t *string_list_remove_head(string_list_t *list) {
  return string_list_remove_node(list, list->head);
}

string_node_t *string_list_remove_node(string_list_t *list,
                                       string_node_t *node) {
  if (!node) {
    return NULL;
  }
  if (node->prev) {
    node->prev->next = node->next;
  }
  if (node->next) {
    node->next->prev = node->prev;
  }
  if (list->head == node) {
    list->head = node->next;
  }
  string_node_remove(node);
  return node;
}

void string_list_delete_node(string_list_t *list, string_node_t *node) {
  string_node_t *removed_node = string_list_remove_node(list, node);
  if (removed_node) {
    string_node_free(removed_node);
  }
}