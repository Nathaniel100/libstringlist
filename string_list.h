#ifndef STRING_LIST_H
#define STRING_LIST_H

#include "string_slice.h"

#ifdef __cplusplus
extern "C" {
#endif

struct string_node;
typedef struct string_node string_node_t;

struct string_list;
typedef struct string_list string_list_t;

//struct string_list_iterator;
//typedef struct string_list_iterator string_list_iterator_t;

struct string_node {
  string_t *str;
  string_node_t *prev;
  string_node_t *next;
};

struct string_list {
  string_node_t *head;
};

typedef void (*string_handler_t)(string_t *s);

string_node_t *string_node_make_empty();
string_node_t *string_node_make(string_t *str);
void string_node_free(string_node_t *node);

string_list_t *string_list_make();
void string_list_free(string_list_t *list);
bool string_list_empty(const string_list_t *list);
string_node_t *string_list_insert_before_head(string_list_t *list,
                                              string_node_t *node);
string_node_t *string_list_insert_after_head(string_list_t *list,
                                             string_node_t *node);
string_node_t *string_list_insert_before(string_list_t *list,
                                         string_node_t *base,
                                         string_node_t *node);
string_node_t *string_list_insert_after(string_list_t *list,
                                        string_node_t *base,
                                        string_node_t *node);
string_node_t *string_list_find(string_list_t *list, const string_t *str);
string_node_t *string_list_find_cstr(string_list_t *list, const char *str);
string_node_t *string_list_remove_head(string_list_t *list);
string_node_t *string_list_remove_node(string_list_t *list, string_node_t *node);
void string_list_delete_node(string_list_t *list, string_node_t *node);

//string_list_iterator_t *string_list_begin(string_list_t *list);
//string_list_iterator_t *string_list_next(string_list_iterator_t *iterator);
//void string_list_foreach(string_list_t *list, string_handler_t string_handler);

#ifdef __cplusplus
}
#endif

#endif