/******************************
** Author : Adarsh Shaw
** title  : statement.h
** date   : 2023-05-13
******************************/

#ifndef ad_statement_h
#define ad_statement_h
#include "input_buffer.h"

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED
} MetaCommandResult;

MetaCommandResult do_meta_command(InputBuffer* input_buffer);

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct {
  StatementType type;
} Statement;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

PrepareResult prepare_statement(InputBuffer* input_buffer,Statement* statement);

void execute_statement(Statement* statement);

#endif //ad_statement_h
