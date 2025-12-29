#ifndef STORAGE_H
#define STORAGE_H

#include "common.h"
#include "row.h"

#define TABLE_MAX_PAGES 100
extern const uint32_t PAGE_SIZE;
extern const uint32_t ROWS_PER_PAGE;
extern const uint32_t TABLE_MAX_ROWS;

typedef struct
{
    int file_descriptor;
    uint32_t file_length;
    void *pages[TABLE_MAX_PAGES];
} Pager;

typedef struct
{
    Pager *pager;
    uint32_t num_rows;
} Table;

typedef struct
{
    Table *table;
    uint32_t row_num;
    bool end_of_table;
} Cursor;

Table *db_open(const char *filename);
void db_close(Table *table);
void *cursor_value(Cursor *cursor);
void cursor_advance(Cursor *cursor);
Cursor *table_start(Table *table);
Cursor *table_end(Table *table);

#endif
