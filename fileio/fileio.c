#include "fileio.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NEWLINE '\n'
#define TERM '\0'
#define GROWTH_FACTOR 2
#define INITIAL_SIZE 32


void _update_status(fio_Status *status, fio_Status value) {
    if (status != NULL) *status = value;
}

char* _grow_array(char *array, int *cur_size) {
    int new_size = *cur_size * GROWTH_FACTOR;

    array = realloc(array, sizeof(char) * new_size);
    if (array == NULL) return NULL;

    *cur_size = new_size;
    return array;
}

bool _char_in_str(char *string, char c) {
    int index = 0;
    while (string[index] != TERM) {
        if (string[index] == c) return true;
        index++;
    }
    return false;
}

char* _read_till_char(FILE *stream, int *str_len, fio_Status *status,
    char *end_chars) {
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

    while (true) {
        cur_char = getc(stream);
        if (_char_in_str(end_chars, cur_char)) {
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

char* fio_read_line(FILE *stream, int *str_len, fio_Status *status) {
    char checking[3];
    checking[0] = NEWLINE;
    checking[1] = EOF;
    checking[2] = TERM;

    return _read_till_char(stream, str_len, status, checking);
}

char* fio_read_file(FILE *stream, int *str_len, fio_Status *status) {
    char checking[2];
    checking[0] = EOF;
    checking[1] = TERM;

    return _read_till_char(stream, str_len, status, checking);
}
