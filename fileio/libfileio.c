#include "fileio.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NEWLINE '\n'
#define TERM '\0'
#define GROWTH_FACTOR 2
#define INITIAL_SIZE 32


void* _grow_array(void *array, int *cur_size, size_t type_size) {
    int new_size = *cur_size * GROWTH_FACTOR;

    array = realloc(array, type_size * new_size);
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

fio_DataRead* _return_empty_status(fio_Status status) {
    fio_DataRead *data = malloc(sizeof(fio_DataRead));
    if (data == NULL) return NULL;
    data->status = status;
    data->lines = NULL;
    data->str_lens = NULL;
    data->length = 0;
    return data;
}

/**
 * A function to read from file till one of the chars in $end_chars.
 * This is the function does the actually reading from the file, the
 * other read functions in the file are just wrappers for this one.
 */
char* _read_till_char(FILE *f, int *str_len, fio_Status *status, char *end_chars) {
    if (f == NULL) {
        *status = FIO_NULL_ERR;
        return NULL;
    }

    int index = 0;
    char cur_char;
    int cur_size = INITIAL_SIZE;

    char *string = malloc(sizeof(char) * cur_size);
    if (string == NULL) {
        *status = FIO_MEM_ERR;
        return NULL;
    }

    while (true) {
        cur_char = getc(f);
        if (_char_in_str(end_chars, cur_char)) {
            break;
        }

        string[index] = cur_char;
        index++;

        // should never be greater than.
        if (index >= cur_size) {
            char *ns = (char*) _grow_array(string, &cur_size, sizeof(char));
            if (ns == NULL) {
                free(string);
                *status = FIO_MEM_ERR;
                return NULL;
            }

            string = ns;
        }
    }

    if (index == 0 && cur_char == EOF) {
        free(string);
        *status = FIO_EOF;
        return NULL;
    }

    string[index] = '\0';
    {
        int total_size = index + 1;
        char *ns = realloc(string, sizeof(char) * total_size);
        if (ns == NULL) {
            free(string);
            *status = FIO_MEM_ERR;
            return NULL;
        }
        string = ns;
    }

    if (str_len != NULL) {
        *str_len = index;
    }

    *status = FIO_SUCCESS;
    
    return string;
}

fio_DataRead* _read_till_chars_into_struct(FILE *stream, char *end_chars) {
    int length;
    fio_Status status;
    fio_DataRead *data = malloc(sizeof(fio_DataRead));
    if (data == NULL) return NULL;

    char *string = _read_till_char(stream, &length, &status, end_chars);

    if (string == NULL) {
        return _return_empty_status(status);
    }

    // Only a single line to be stored
    data->str_lens = malloc(sizeof(int));
    data->lines = malloc(sizeof(char*));
    if (data->str_lens == NULL || data->lines == NULL) {
        free(string);
        fio_free_DataRead(data);
        return _return_empty_status(FIO_MEM_ERR);
    }

    data->length = 1;
    *(data->str_lens) = length;
    *(data->lines) = string;
    data->status = status;

    return data;
}

fio_DataRead* fio_read_line(FILE *stream) {
    char end_chars[3];
    end_chars[0] = NEWLINE;
    end_chars[1] = EOF;
    end_chars[2] = TERM;

    return _read_till_chars_into_struct(stream, end_chars);
}

fio_DataRead* fio_read_file(FILE *stream) {
    char end_chars[2];
    end_chars[0] = EOF;
    end_chars[1] = TERM;

    return _read_till_chars_into_struct(stream, end_chars);
}

fio_DataRead* fio_read_lines(FILE *stream) {
    char end_chars[3];
    end_chars[0] = NEWLINE;
    end_chars[1] = EOF;
    end_chars[2] = TERM;

    fio_DataRead *data = malloc(sizeof(fio_DataRead));
    if (data == NULL) return NULL;

    int sl_cap = INITIAL_SIZE, l_cap = INITIAL_SIZE;
    data->str_lens = malloc(sizeof(int) * sl_cap);
    data->lines = malloc(sizeof(char*) * l_cap);
    data->length = 0;

    if (data->str_lens == NULL || data->lines == NULL) {
        fio_free_DataRead(data);
        return _return_empty_status(FIO_MEM_ERR);
    }

    int length;
    int index = 0;
    fio_Status status;

    while (true) {
        char *string = _read_till_char(stream, &length, &status, end_chars);
        if (string == NULL && status != FIO_EOF) {
            fio_free_DataRead(data);
            return _return_empty_status(status);
        }

        if (string == NULL) {
            data->status = FIO_SUCCESS;
            return data;
        }

        if (index >= sl_cap) {
            char **ns = (char **) _grow_array(data->lines, &l_cap, sizeof(char*));
            int *ln = (int *) _grow_array(data->str_lens, &sl_cap, sizeof(int));

            if (ns == NULL || ln == NULL) {
                free(ns);
                free(ln);
                fio_free_DataRead(data);
                return _return_empty_status(FIO_MEM_ERR);
            }

            data->lines = ns;
            data->str_lens = ln;
        }

        data->lines[index] = string;
        data->str_lens[index] = length;
        index++;
    }

    return data;
}

void fio_free_DataRead(fio_DataRead *fdr) {
    if (fdr == NULL) return;

    if (fdr->lines == NULL) {
        free(fdr->str_lens);  // may or may not be null.
        free(fdr);
        return;
    }

    for (int i = 0; i < fdr->length; i++) {
        free(fdr->lines[i]);
    }

    free(fdr->lines);
    free(fdr->str_lens);
    free(fdr);
}

fio_Status fio_write_line(FILE *stream, char *string) {
    if (stream == NULL || string == NULL) return FIO_NULL_ERR;
    fputs(string, stream);
    fflush(stream);
    return FIO_SUCCESS;
}

fio_Status fio_write_lines(FILE *stream, char **str_arr, int arr_len, char* delimiter) {
    if (stream == NULL || str_arr == NULL) return FIO_NULL_ERR;

    for (int i = 0; i < arr_len; i++) {
        fputs(str_arr[i], stream);
        if (i != (arr_len - 1) && delimiter != NULL) fputs(delimiter, stream);
    }
    fflush(stream);
    return FIO_SUCCESS;
}

fio_Status fio_write_file(FILE *stream, char *string) {
    return fio_write_line(stream, string);
}
