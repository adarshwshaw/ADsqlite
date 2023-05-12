/******************************
** Author : Adarsh Shaw
** title  : statement.h
** date   : 2023-05-13
******************************/

#ifndef ad_statement_h
#define ad_statement_h
#include <stdint.h>
#include "input_buffer.h"

typedef struct _table Table;

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED
} MetaCommandResult;

MetaCommandResult do_meta_command(InputBuffer* input_buffer,Table* table);

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

// row is hardcode for now
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

static const uint32_t ID_SIZE = size_of_attribute(Row, id);
static const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
static const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
static const uint32_t ID_OFFSET = 0;
static const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
static const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
static const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

void serialize_row(Row* source, void* dst);
void deserialize_row(void* src, Row* destination);
void* row_slot(Table* table, uint32_t row_num);
void print_row(Row* row);

static const uint32_t PAGE_SIZE = 4096;
#define TABLE_MAX_PAGES 100
static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

struct _table{
  uint32_t num_rows;
  void* pages[TABLE_MAX_PAGES];
};

Table* new_table();
void free_table(Table* table);

typedef struct {
  StatementType type;
  Row row_to_insert;
} Statement;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

PrepareResult prepare_statement(InputBuffer* input_buffer,Statement* statement);

typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL 
} ExecuteResult;

ExecuteResult execute_insert(Statement* statement, Table* table);
ExecuteResult execute_select(Statement* statement, Table* table);
ExecuteResult execute_statement(Statement* statement, Table* table);

#endif //ad_statement_h
