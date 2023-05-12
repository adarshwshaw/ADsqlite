#include "input_buffer.h"
#include <stdio.h>
#include <stdlib.h>

InputBuffer* new_input_buffer(){
    InputBuffer* buf = calloc(1,sizeof(*buf));
    return buf;
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}
