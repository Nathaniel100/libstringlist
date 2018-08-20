
#include "string_slice.h"
#include "def.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct string {
  refcnt_t ref;
  char *str;
  uint32_t size;
  uint32_t alloc;
  string_t *slice;
};

string_t *string_make_claim(char *str, uint32_t size, uint32_t alloc) {
  string_t *s = (string_t *) malloc(sizeof(string_t));
  if (!s) {
    return NULL;
  }
  s->ref = 1;
  s->str = str;
  s->size = size;
  s->alloc = alloc;
  s->slice = NULL;
  return s;
}

string_t *string_make_empty(uint32_t size) {
  uint32_t alloc = power2(size);
  char *str = (char *) malloc(alloc);
  if (!str) {
    return NULL;
  }
  return string_make_claim(str, 0, alloc);
}

string_t *string_make_slice(string_t *s, uint32_t start, uint32_t len) {
  string_t *slice = NULL;

  if (start > s->size || len > s->size || start + len > s->size) {
    return NULL;
  }
  if (start == 0 && len == s->size) {
    string_add_ref(s);
    return s;
  }
  slice = (string_t *) malloc(sizeof(string_t));
  if (!slice) {
    return NULL;
  }

  slice->ref = 1;
  slice->str = s->str + start;
  slice->size = len;
  slice->alloc = len;
  slice->slice = s;
  string_add_ref(s);

  return slice;
}

string_t *string_make_copy_cstr(const char *str) {
  return string_make_copy(str, strlen(str));
}

string_t *string_make_copy(const char *str, uint32_t len) {
  string_t *s = string_make_empty(len);
  if (!s) {
    return NULL;
  }
  string_append_buf(s, str, len);
  return s;
}

void string_add_ref(string_t *s) { add_ref(&s->ref); }

void string_del_ref(string_t *s) {
  if (!del_ref(&s->ref)) {
    return;
  }

  if (s->slice) {
    string_del_ref(s->slice);
  } else {
    if (s->str) {
      free(s->str);
    }
  }
  s->str = NULL;
  s->slice = NULL;
  free(s);
}

bool string_append_str(string_t *target, string_t *s) {
  return string_append_buf(target, s->str, s->size);
}

bool string_append_buf(string_t *target, const char *str, uint32_t len) {
  if (target->slice) {
    return false;
  }
  if (len + target->size > target->alloc) {
    uint32_t alloc = power2(len + target->size);
    char *new_str = (char *) malloc(alloc);
    char *old_str = target->str;
    if (!new_str) {
      return false;
    }
    memmove(new_str, target->str, target->size);
    target->str = new_str;
    target->alloc = alloc;
    if (old_str) {
      free(old_str);
    }
  }

  if (len > 0) {
    memmove(target->str + target->size, str, len);
    target->size += len;
  }

  return true;
}

bool string_append_cstr(string_t *target, const char *str) {
  return string_append_buf(target, str, strlen(str));
}

int string_compare(const string_t *a, const string_t *b) {
  int cmp = memcmp(a->str, b->str, min(a->size, b->size));
  if (cmp != 0) {
    return cmp;
  }
  if (a->size == b->size) {
    return 0;
  }
  return a->size > b->size ? 1 : -1;
}

bool string_equals(const string_t *a, const string_t *b) {
  return string_compare(a, b) == 0;
}

bool string_equals_cstr(const string_t *s, const char *str) {
  uint32_t len = strlen(str);
  if (len != s->size) {
    return false;
  }
  return memcmp(s->str, str, len) == 0;
}

bool string_equals_ignorecase(const string_t *a, const string_t *b) {
  if (a->size != b->size) {
    return false;
  }

  for (uint32_t i = 0; i < a->size; i++) {
    if (tolower(a->str[i]) != tolower(b->str[i])) {
      return false;
    }
  }
  return true;
}

uint32_t string_size(const string_t *s) { return s->size; }

const char *string_data(const string_t *s) { return s->str; }

void string_reset(string_t *s) { s->size = 0; }

char *string_to_cstr(const string_t *s) {
  char *str = (char *) malloc(s->size + 1);
  if (!str) {
    return NULL;
  }
  memcpy(str, s->str, s->size);
  str[s->size] = '\0';
  return str;
}

bool string_vprintf(string_t *s, const char *format, va_list arg) {
  char buffer[1024] = {0};

  string_reset(s);
  vsnprintf(buffer, sizeof(buffer), format, arg);
  return string_append_cstr(s, buffer);
}

bool string_printf(string_t *s, const char *format, ...) {
  va_list arg;
  bool result;

  va_start(arg, format);
  result = string_vprintf(s, format, arg);
  va_end(arg);
  return result;
}

bool string_append_vprintf(string_t *s, const char *format, va_list arg) {
  char buffer[1024] = {0};

  vsnprintf(buffer, sizeof(buffer), format, arg);
  return string_append_cstr(s, buffer);
}
bool string_append_printf(string_t *s, const char *format, ...) {
  va_list arg;
  bool result;

  va_start(arg, format);
  result = string_append_vprintf(s, format, arg);
  va_end(arg);
  return result;
}
