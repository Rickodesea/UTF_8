#include "utf_8.h"

#define READ_1_BYTE 1
#define READ_2_BYTE 2
#define READ_3_BYTE 3
#define READ_4_BYTE 4
#define READ_ERROR -1

int utf_8_error_code = 0;
uint utf_8_error_byte = 0;

static const uint byte_1_flag = 128;
static const uint byte_2_flag = 128+64+32;
static const uint byte_3_flag = 128+64+32+16;
static const uint byte_4_flag = 128+64+32+16+8;

static const uint byte_1_true = 0;
static const uint byte_2_true = 128+64;
static const uint byte_3_true = 128+64+32;
static const uint byte_4_true = 128+64+32+16;

static uint get_value_top4bits(uint byte_value);
static int is_little_endian();
static uint reverseUInt (uint i);

int utf_8_get_id(const char* const charbuf, utf_8_id* const id){
  //** params can not be null **//
  if(charbuf == 0){
    utf_8_error_byte = 0;
    utf_8_error_code = UTF_8_ERROR_NULL_CHARBUF;
    return UTF_8_FAILED;
  }

  if(id == 0){
    utf_8_error_byte = 0;
    utf_8_error_code = UTF_8_ERROR_NULL_UTF8POS;
    return UTF_8_FAILED;
  }

  //get char at desired position : char_start
  const uint char_start = charbuf[id->in_char_position];

  //** get how many bytes should be read **//
  const uint read = get_value_top4bits(char_start);

  //check for error
  if(read == READ_ERROR) return UTF_8_FAILED;

  //read bytes
  id->out_utf_id = 0;
  id->out_utf_size = read;
  uchar bytes[] = {0, 0, 0, 0};
  for(uint i = 0; i < read; i++){
    uint char_value = charbuf[id->in_char_position + i];
    bytes[i] = char_value;
  }
  id->out_utf_id = reverseUInt(*((uint*)bytes));

  return UTF_8_SUCCEEDED;
}

int utf_8_count_id_in_string(const char* const string, uint* const count){
  //** params can not be null **//
  if(string == 0){
    utf_8_error_byte = 0;
    utf_8_error_code = UTF_8_ERROR_NULL_CHARBUF;
    return UTF_8_FAILED;
  }

  if(count == 0){
    utf_8_error_byte = 0;
    utf_8_error_code = UTF_8_ERROR_NULL_COUNT;
    return UTF_8_FAILED;
  }

  //** read each utf id and count it **//
  utf_8_id id = {0};
  *count = 0;
  do{
    int result = utf_8_get_id(string, &id);
    if(result == UTF_8_FAILED) return UTF_8_FAILED;

    if(id.out_utf_id != 0) (*count)++;

    id.in_char_position += id.out_utf_size;

  } while(id.out_utf_id != 0);

  return UTF_8_SUCCEEDED;
}

int utf_8_count_id(const char* const charbuf, const uint char_start_pos, const uint buf_length, uint* const count){
  //** params can not be null **//
  if(charbuf == 0){
    utf_8_error_byte = 0;
    utf_8_error_code = UTF_8_ERROR_NULL_CHARBUF;
    return UTF_8_FAILED;
  }

  if(count == 0){
    utf_8_error_byte = 0;
    utf_8_error_code = UTF_8_ERROR_NULL_COUNT;
    return UTF_8_FAILED;
  }

  //** read each utf id and count it **//
  utf_8_id id = {0};
  id.in_char_position = char_start_pos;
  *count = 0;
  do{
    int result = utf_8_get_id(charbuf, &id);
    if(result == UTF_8_FAILED) return UTF_8_FAILED;

    (*count)++;

    id.in_char_position += id.out_utf_size;

  } while((id.in_char_position - char_start_pos) < buf_length);

  return UTF_8_SUCCEEDED;
}

static uint get_value_top4bits(uint byte_value){
  if((byte_value & byte_1_flag) == byte_1_true) return READ_1_BYTE;
  if((byte_value & byte_2_flag) == byte_2_true) return READ_2_BYTE;
  if((byte_value & byte_3_flag) == byte_3_true) return READ_3_BYTE;
  if((byte_value & byte_4_flag) == byte_4_true) return READ_4_BYTE;

  //error code for unrecognize byte
  utf_8_error_byte = byte_value;
  utf_8_error_code = UTF_8_ERROR_UNKNOWN_CHAR;

  return READ_ERROR;
}

static int is_little_endian() {
    int i = 1;
    char* p = (char*)&i;

    if (p[0] == 1) return 1;

    return 0;
}

static uint reverseUInt (uint i) {
    uchar c1, c2, c3, c4;

    if(is_little_endian() == 1) {
        return i;
    }

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return (uint)(((uint)c1 << 24) + ((uint)c2 << 16) + ((uint)c3 << 8) + c4);
}
