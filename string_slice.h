#ifndef STRING_SLICE_H
#define STRING_SLICE_H

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "refcnt.h"

#ifdef __cplusplus
extern "C" {
#endif

struct string;
typedef struct string string_t;

string_t *string_make_claim(char *str, uint32_t size, uint32_t alloc);
string_t *string_make_empty(uint32_t size);
string_t *string_make_slice(string_t *s, uint32_t start, uint32_t len);
string_t *string_make_copy_cstr(const char *str);
string_t *string_make_copy(const char *str, uint32_t len);
void string_add_ref(string_t *s);
void string_del_ref(string_t *s);
bool string_append_str(string_t *target, string_t *s);
bool string_append_buf(string_t *target, const char *str, uint32_t len);
bool string_append_cstr(string_t *target, const char *str);
int string_compare(const string_t *a, const string_t *b);
bool string_equals(const string_t *a, const string_t *b);
bool string_equals_cstr(const string_t *s, const char *str);
bool string_equals_ignorecase(const string_t *a, const string_t *b);
uint32_t string_size(const string_t *s);
// 返回的并不是以\0结尾的
const char *string_data(const string_t *s);
void string_reset(string_t *s);
char *string_to_cstr(const string_t *s); 
bool string_vprintf(string_t *s, const char *format, va_list arg);
bool string_printf(string_t *s, const char *format, ...);
bool string_append_vprintf(string_t *s, const char *format, va_list arg);
bool string_append_printf(string_t *s, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif