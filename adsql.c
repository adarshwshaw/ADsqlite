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
#include "input_buffer.h"
#include "statement.h"

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
    // Ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

int main(int argc, char const *argv[]){
    if (argc < 2) {
        printf("Must supply a database filename.\n");
        exit(EXIT_FAILURE);
    }

    const char* filename = argv[1];
    Table* table = db_open(filename);
    InputBuffer* input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.') {
            switch (do_meta_command(input_buffer,table)) {
            case (META_COMMAND_SUCCESS):
                continue;
            case (META_COMMAND_UNRECOGNIZED):
                printf("Unrecognized command '%s'\n", input_buffer->buffer);
                continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer,&statement))
        {
        case PREPARE_SUCCESS:
            break;
        case (PREPARE_SYNTAX_ERROR):
            printf("Syntax error. Could not parse statement.\n");
            continue;
        case (PREPARE_STRING_TOO_LONG):
            printf("String too long.\n");
            continue;
        case (PREPARE_NEGATIVE_ID):
            printf("Id must be positive.\n");
            continue;
        case PREPARE_UNRECOGNIZED_STATEMENT:
            printf("Unrecognized keyword at start of '%s'.\n",
                input_buffer->buffer);
            continue;
        }
        switch (execute_statement(&statement, table)) {
            case (EXECUTE_SUCCESS):
                printf("Executed.\n");
                break;
            case (EXECUTE_TABLE_FULL):
                printf("Error: Table full.\n");
                break;
        }
    }
}
