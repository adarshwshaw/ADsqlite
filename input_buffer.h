/******************************
** Author : Adarsh Shaw
** title  : input_buffer.h
** date   : 2023-05-13
******************************/
#ifndef ad_input_buffer_h
#define ad_input_buffer_h
#include "posix.h"

typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer();

void close_input_buffer(InputBuffer* input_buffer);

#endif //ad_input_buffer_h
