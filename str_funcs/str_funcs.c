#include "str_funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TERM '\0'
#define WHITESPACES " \n\t"


/**
 * Same as sf_char_in_str but does not perform checks.
 */
bool _char_in_str(char *s, char c);

/**
 * Count the number of characters in the start
 * that belong to a particular set of chars.
 */
int _count_char_start(char *s, char *chars);

/**
 * Count the number of characters in the end
 * that belong to a particular set of chars 
 * and get the length of the string.
 */
int _count_char_end_and_length(char *s, char *chars, int *length_dest);

/**
 * Convert a character to upper case.
 */
char _char_to_upper(char c);

/**
 * Convert a character to lower case.
 */
char _char_to_lower(char c);

bool _char_in_str(char *s, char c) {
    int index = 0;
    while (s[index] != TERM) {
        if (s[index] == c) return true;
        index++;
    }

    return false;
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

char _char_to_upper(char c) {
    if (c >= 'a' && c <= 'z') return c - 32;
    else return c;
}

char _char_to_lower(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32;
    else return c;
}


bool sf_char_in_str(char *string, char c) {
    if (string == NULL) return false;
    if (c == TERM) return true;

    return _char_in_str(string, c);
}

char* sf_trim_chars(char *string, char *chars) {
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

char* sf_trim_whitespace(char *string) {
    return sf_trim_chars(string, WHITESPACES);
}

bool sf_is_substring(char* string, char *substring) {
    return sf_index_of(string, substring, 0) != -1;
}

char* sf_get_substring(char *string, int start, int end, int step) {
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

char* sf_duplicate_string(char *string) {
    if (string == NULL) return NULL;

    int length = strlen(string);
    char *new = malloc(sizeof(char) * (length + 1));
    if (new == NULL) return NULL;

    for (int i=0; i<length; i++) {
        new[i] = string[i];
    }

    new[length] = TERM;
    return new;
}

void sf_to_uppercase(char* string) {
    if (string == NULL) return;

    char *ptr = string;
    while (*ptr != TERM) {
        *ptr = _char_to_upper(*ptr);
        ptr++;
    }
}

void sf_to_lowercase(char* string) {
    if (string == NULL) return;

    char *ptr = string;
    while (*ptr != TERM) {
        *ptr = _char_to_lower(*ptr);
        ptr++;
    }
}

int sf_index_of(char *string, char *substring, int start) {
    
    if (string == NULL || substring == NULL) {
        return -1;
    }

    // If substring is empty
    if (substring[0] == TERM) {
        return 0;
    }

    // Handle negative indices
    if (start < 0) {
        start = strlen(string) + start;
        // Handle negative index out of bounds
        if (start < 0) {
            return -1;
        }
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

int sf_index_of_reverse(char *string, char *substring, int start) {

    if (string == NULL || substring == NULL) {
        return -1;
    }

    // If substring is empty
    if (substring[0] == TERM) {
        return 0;
    }

    int s_len = strlen(string);
    int b_len = strlen(substring);
    char *p1 = string + (s_len - 1);
    char *p2 = substring + (b_len - 1);
    char* pos = NULL;


    // Break if ever p = bound
    char *s_bound = string - 1;
    char *b_bound = substring - 1;

    // Negative indices
    if (start < 0) {
        start = start + s_len;
        // Negative index out of bounds
        if (start < 0) return -1;
    }

    // Last character has index s_len - 1
    for (int i = 0; i < ((s_len - 1) - start); i++) {
        if (p1 <= s_bound) return -1;
        p1--;
    }

    while (true) {
        if (p2 == b_bound) {
            if (pos == NULL) return -1;
            else return (int)(pos - string - (b_len - 1));
        }

        if (p1 == s_bound) {
            return -1;
        }

        if (*p1 == *p2) {
            if (pos == NULL) pos = p1;
            p1--;
            p2--;
        } else if (pos != NULL){
            p2 = substring + (b_len - 1);
            p1 = pos - 1;
            pos = NULL;
        } else {
            p1--;
        }
    }

    return -1;
}

char** sf_split_string(char *string, char *substring) {
    // TODO: Complete function
    return NULL;
}

char** sf_split_string_inplace(char *string, char *substring) {
    // TODO: Complete function
    return NULL;
}

void sf_free_split_string(char** split_array) {
    // TODO: Complete function
}
