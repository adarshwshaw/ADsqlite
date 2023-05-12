/******************************
** Author : Adarsh Shaw
** title  : adsql.c
** date   : 2023-05-12
******************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "posix.h"

typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer(){
    InputBuffer* buf = calloc(1,sizeof(*buf));
    return buf;
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

void print_prompt(){
    printf("db> ");
}

void read_input(InputBuffer* input_buffer){
    ssize_t bytes_read =getline(&(input_buffer->buffer), 
        &(input_buffer->buffer_length), stdin);
    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    // my version does not take trailing newline
    // Ignore trailing newline
//   input_buffer->input_length = bytes_read - 1;
//   input_buffer->buffer[bytes_read - 1] = 0;
}

int main(int argc, char const *argv[])
{
    InputBuffer* input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit") == 0) {
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
        } else {
        printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
    }
}
