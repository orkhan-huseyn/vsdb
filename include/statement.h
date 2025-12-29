#ifndef STATEMENT_H
#define STATEMENT_H

#include "common.h"
#include "row.h"
#include "storage.h"
#include "input_buffer.h"

typedef struct
{
  StatementType type;
  Row row_to_insert;
} Statement;

PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);
void execute_statement(Statement *statement, Table *table);

#endif
