#include "common.h"
#include "input_buffer.h"
#include "storage.h"
#include "statement.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_prompt() { printf("db > "); }

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Must supply a database filename.\n");
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    Table *table = db_open(filename);
    InputBuffer *input_buffer = new_input_buffer();

    while (true)
    {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.')
        {
            if (strcmp(input_buffer->buffer, ".exit") == 0)
            {
                close_input_buffer(input_buffer);
                db_close(table);
                exit(EXIT_SUCCESS);
            }
            else
            {
                printf("Unrecognized command '%s'.\n", input_buffer->buffer);
                continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement))
        {
        case PREPARE_SUCCESS:
            execute_statement(&statement, table);
            break;
        case PREPARE_SYNTAX_ERROR:
            printf("Syntax error. Could not parse statement.\n");
            break;
        case PREPARE_STRING_TOO_LONG:
            printf("String is too long.\n");
            break;
        case PREPARE_NEGATIVE_ID:
            printf("ID must be positive.\n");
            break;
        case PREPARE_UNRECOGNIZED_STATEMENT:
            printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
            break;
        }
    }

    return EXIT_SUCCESS;
}
