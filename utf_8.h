#ifndef _H_UTF_8_UTF_8
#define _H_UTF_8_UTF_8

#include "main.h"

#define UTF_8_ERROR_NULL_CHARBUF -10
#define UTF_8_ERROR_NULL_UTF8POS -11
#define UTF_8_ERROR_NULL_COUNT -12
#define UTF_8_ERROR_UNKNOWN_CHAR -13

typedef struct {
  ulong in_char_position;
  uint out_utf_size;
  uint out_utf_id;
} utf_8_id;

extern int utf_8_error_code;
extern uint utf_8_error_byte;

int utf_8_get_id(const char* const charbuf, utf_8_id* const id);
int utf_8_count_id_in_string(const char* const string, uint* const count);
int utf_8_count_id(const char* const charbuf, const uint char_start_pos, const uint buf_length, uint* const count);

#endif //_H_UTF_8_UTF_8
