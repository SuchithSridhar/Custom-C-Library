#include "str_funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TERM '\0'
#define WHITESPACES " \n\t"

/**
 * same as char_in_str but doesn't NULL perform checks
 */
bool _char_in_str(char *s, char c) {
    int index = 0;
    while (s[index] != TERM) {
        if (s[index] == c) return true;
        index++;
    }
    return false;
}

bool char_in_str(char *string, char c) {
    if (string == NULL) return false;
    if (c == TERM) return true;

    return _char_in_str(string, c);
}


int _count_char_start(char *s, char *chars) {
    int index = 0;
    while (s[index] != TERM) {
        if (!_char_in_str(chars, s[index])) break;
        index++;
    }
    return index;
}


/**
 * Count chars at the end and total length.
 * Total length does not include \0.
 */
int _count_char_end_and_length(char *s, char *chars, int *length_dest) {
    int index = 0;
    int count = 0;
    while (s[index] != TERM) {
        if (_char_in_str(chars, s[index])) {
            count++;
        } else {
            count = 0;
        }
        index++;
    }

    if (length_dest != NULL) *length_dest = index;
    return count;
}


char* trim_chars(char *string, char *chars) {
    // Iterate over the string 2x to first
    // calculate the size of the new string
    // and then actually build it. This is
    // done to make only one call to malloc.
    
    int pre_chars = _count_char_start(string, chars);
    int length;
    int post_chars = _count_char_end_and_length(string+pre_chars, chars, &length);
    int size = (length - post_chars) + 1;

    char *new = malloc(sizeof(char) * size);

    for (int i = 0; i < size-1; i++) {
        new[i] = string[pre_chars+i];
    }

    new[size-1] = TERM;
    return new;
}

char* trim_whitespace(char *string) {
    return trim_chars(string, WHITESPACES);
}

bool is_substring(char* string, char *substring) {
    return index_of(string, substring, 0) != -1;
}

char* get_substring(char *string, int start, int end, int step) {
    if (string == NULL) return NULL;

    int length = strlen(string);

    if (start < 0) start = length + start;
    if (end < 0) end = length + end;

    int difference = end > start ? (end - start) : (start - end);
    int abs_step = step > 0 ? step : -step;
    int new_length = (difference + 1*(abs_step)) / abs_step;

    // +1 for the '\0'
    char *new_string = malloc(sizeof(char) * (new_length + 1));
    if (new_string == NULL) return NULL; 

    int current = start;

    for (int i = 0; i < new_length; i++) {
        new_string[i] = string[current];
        current += step;
    }

    new_string[new_length] = TERM;

    return new_string;
}

char _char_to_upper(char c) {
    if (c >= 'a' && c <= 'z') return c - 32;
    else return c;
}

char _char_to_lower(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32;
    else return c;
}

char* to_uppercase(char* string) {
    if (string == NULL) return NULL;

    int length = strlen(string);

    char *new = malloc(sizeof(char) * (length + 1));
    if (new == NULL) return NULL;

    for (int i = 0; i < length; i++) {
        new[i] = _char_to_upper(string[i]);
    }

    new[length] = TERM;

    return new;
}

char* to_lowercase(char* string) {
    if (string == NULL) return NULL;

    int length = strlen(string);

    char *new = malloc(sizeof(char) * (length + 1));
    if (new == NULL) return NULL;

    for (int i = 0; i < length; i++) {
        new[i] = _char_to_lower(string[i]);
    }

    new[length] = TERM;

    return new;
}


int index_of(char *string, char *substring, int start) {
    
    if (string == NULL || substring == NULL) {
        return -1;
    }

    // If substring is empty
    if (substring[0] == TERM) {
        return 0;
    }

    char *p1 = string;
    char *p2 = substring;
    char* pos = NULL;

    for (int i = 0; i < start; i++) {
        if (*p1 == TERM) return -1;
        p1++;
    }

    while (true) {
        if (*p2 == TERM) {
            if (pos == NULL) return -1;
            else return (int)(pos - string);
        }

        if (*p1 == TERM) {
            return -1;
        }

        if (*p1 == *p2) {
            if (pos == NULL) pos = p1;
            p1++;
            p2++;
        } else if (pos != NULL){
            p2 = substring;
            p1 = pos + 1;
            pos = NULL;
        } else {
            p1++;
        }
    }

    return -1;
}

int index_of_reverse(char *string, char *substring, int start) {
    // TODO: Complete function
    return 0;
}

char** split_string(char *string, char *substring) {
    // TODO: Complete function
    return NULL;
}

char** split_string_inplace(char *string, char *substring) {
    // TODO: Complete function
    return NULL;
}

void free_split_string(char** split_array) {
    // TODO: Complete function
}
