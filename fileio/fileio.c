#include "fileio.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NEWLINE '\n'
#define GROWTH_FACTOR 2
#define INITIAL_SIZE 32


void _update_status(FIO_STATUS *status, FIO_STATUS value) {
    if (status != NULL) *status = value;
}

char* _grow_array(char *array, int *cur_size) {
    int new_size = *cur_size * GROWTH_FACTOR;

    array = realloc(array, sizeof(char) * new_size);
    if (array == NULL) return NULL;

    *cur_size = new_size;
    return array;
}

char* read_line(FILE *stream, int *str_len, FIO_STATUS *status) {
    if (stream == NULL) {
        _update_status(status, FIO_NULL_ERR);
        return NULL;
    }

    int index = 0;
    char cur_char;
    int cur_size = INITIAL_SIZE;

    char *string = malloc(sizeof(char) * cur_size);
    if (string == NULL) {
        _update_status(status, FIO_MEM_ERR);
        return NULL;
    }

    while (1) {
        cur_char = getc(stream);
        if (cur_char == NEWLINE || cur_char == EOF) {
            break;
        }

        string[index] = cur_char;
        index++;

        // should never be greater than.
        if (index >= cur_size) {
            char *ns = _grow_array(string, &cur_size);
            if (ns == NULL) {
                free(string);
                _update_status(status, FIO_MEM_ERR);
                return NULL;
            }

            string = ns;
        }
    }

    if (index == 0 && cur_char == EOF) {
        free(string);
        _update_status(status, FIO_EOF);
        return NULL;
    }

    string[index] = '\0';
    {
        int total_size = index + 1;
        char *ns = realloc(string, sizeof(char) * total_size);
        if (ns == NULL) {
            free(string);
            _update_status(status, FIO_MEM_ERR);
            return NULL;
        }
        string = ns;
    }

    if (str_len != NULL) {
        *str_len = index;
    }

    _update_status(status, FIO_SUCCESS);
    
    return string;
}
