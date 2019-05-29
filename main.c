#include "main.h"
#include <stdio.h>
#include "utf_8.h"
#include <string.h>

static uint major_version = 0;
static uint minor_version = 0;
static uint mini_version = 0;
static uint version_change_count = 0;

static const char* const generic_msg [] = {
  "utf_8", " ", "\n",
  "Algodal™", " ",
  "©2019", " ",
  "Alrick Grandison", "\n"
};

static void print_msg_array(const char* const msg_array[], uint length);
static void print_version(uint major, uint minor, uint mini, uint change);

static int is_little_endian() {
    int i = 1;
    char* p = (char*)&i;

    if (p[0] == 1) return 1;

    return 0;
}

int main(int argc, char* argv[]){
  print_msg_array(generic_msg, sizeof(generic_msg) / sizeof(const char**));
  print_version(major_version, minor_version, mini_version, version_change_count);

  const char* const text = "UTF-8: ©™😀😒😤😸🙋0☯1❤2✿あア";
  uint utf8buf[] = {0, 0};
  utf_8_id id = {0};
  int result = 0;
  uint length = 0;
  uint count = 0;
  uint offset = strlen("UTF-8: ");

  utf_8_count_id_in_string(text, &length);
  utf_8_count_id(text, offset, strlen(text) - offset, &count);

  if(is_little_endian()){
    printf("%s\n", "platform is little endian");
  } else {
    printf("%s\n", "platform is big endian");
  }

  printf("text : %s\n", text);
  printf("offset : %u\n", offset);
  printf("length : %u\n", length);
  printf("count : %u\n", count);

  utf8buf[0] = 0xa9c2;
  printf("test : %s\n", (char*)utf8buf);

  do{
    result = utf_8_get_id(text, &id);
    if(result == UTF_8_FAILED){
      printf("%s : %d (%c)\n", "failed to get id", utf_8_error_code, utf_8_error_byte);
      return -1;
    }

    utf8buf[0] = id.out_utf_id;

    printf(
      "utf-8:\n\tid %u\n\tstring '%s'\n\tsize %d\n",
      id.out_utf_id,
      (const char* const)utf8buf,
      id.out_utf_size);

    //ensure to increment input position else infinite loop
    id.in_char_position += id.out_utf_size;

  } while(id.out_utf_id != 0);

  return 0;
}

static void print_msg_array(const char* const msg_array[], uint length){
  for(uint i = 0; i < length; i++){
    printf("%s", msg_array[i]);
  }
}

static void print_version(uint major, uint minor, uint mini, uint change_count){
  printf("version %d.%d.%d changes %d\n", major, minor, mini, change_count);
}
