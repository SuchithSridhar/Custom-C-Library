#ifndef _SF_STRING_FUNCTIONS_H
#define _SF_STRING_FUNCTIONS_H

#include <stdbool.h>

/**
 * A struct to hold the result of
 * sf_split_string.
 */
typedef struct { 
    /* The array of strings. */
    char **lines;

    /* The length of each of the string in lines. */
    int *strlens;

    /* The length of lines. */
    long length;

} sf_SplitString;

/**
 * Remove a set of characters from the start and
 * end of a string. A new allocated string is returned.
 * @param string the string to trim.
 * @param chars the set of characters to be trimmed as a string.
 * @return a new string allocated on the heap having trimmed $chars.
 */
char *sf_trim_chars(char *string, char *chars);

/**
 * Remove all white-space characters from the start
 * and end of a string. A new allocated string is retuned.
 * @param string the string to trim.
 * @return a new string allocated on the heap having trimmed 
 *         the white space characters.
 */
char *sf_trim_whitespace(char *string);

/**
 * Check if a given character is in a string.
 * @param string the string to look for the character in.
 * @param c the character to look for.
 * @return true if the character was found, else false.
 */
bool sf_char_in_str(char *string, char c);

/**
 * Check is a string is contained within another string.
 * @param string the source string to check within.
 * @param substring the substring to look for.
 * @return true if the substring is contained in the string,
 *         else false.
 */
bool sf_is_substring(char *string, char *substring);

/**
 * Get a substring of the $string based on the range.
 * Indices start from 0 till the len-1 and negative indices
 * run in the reverse order from the end of the string.
 * The Indices are inclusive for both positive and negative values.
 * @param string the source string to derive the substring.
 * @param start the start index in the string.
 * @param stop the end index in the string.
 * @param step the number of characters to step by.
 * @return the substring if string is not NULL.
 */
char* sf_get_substring(char *string, int start, int stop, int step);

/**
 * Copy a string onto the heap.
 * @param string the string to copy.
 * @return a pointer to the copied string, returns NULL on fail.
 */
char* sf_duplicate_string(char *string);

/**
 * Convert a string to upper case in-place.
 * NOTE: Does not work for string literals - will cause segfault.
 * @param string the string to be converted.
 */
void sf_to_uppercase(char *string);

/**
 * Convert a string to lower case in-place.
 * NOTE: Does not work for string literals - will cause segfault.
 * @param string the string to be converted.
 */
void sf_to_lowercase(char *string);

/**
 * Reverse a string in-place.
 * NOTE: Does not work for string literals - will cause segfault.
 * @param string the string to be reversed.
 */
void sf_reverse_string(char *string);

/**
 * Get the index of a substring.
 * The function returns -1 if the substring is not present.
 * The value $start is position to start scanning, it can
 * be either a positive index or a negative index.
 * @param string the source string to check in.
 * @param substring the substring to look for.
 * @param start the position to start at.
 * @return the index of the substring or -1 if not present.
 */
int sf_index_of(char *string, char *substring, int start);

/**
 * Get the index of a substring scanning right to left.
 * The index returned is the index of the first
 * character of the substring in the source string.
 * The function returns -1 if the substring is not present.
 * The value $start is position to start scanning, it can
 * be either a positive index or a negative index.
 * @param string the source string to check in.
 * @param substring the substring to look for.
 * @param start the position to start at.
 * @return the index of the substring or -1 if not present.
 */
int sf_index_of_reverse(char *string, char *substring, int start);

/**
 * Concat a string to an existing string.
 * Returns a new string or appends it to the end of the base string.
 * NOTE: inplace must not true if $base is not on the heap.
 * @param base the base string to append to.
 * @param operand the string to append.
 * @param inplace if true, will append the operand to base and resize if necessary.
 * @return the new combined string.
 */
char* sf_concat(char* base, char* operand, bool inplace);

/**
 * Split a string similar to String.split in java.
 * Note, all the lines are actually stored in a contiguous block
 * and hence only the first pointer needs to be freed.
 * @param string the source string to split.
 * @param substring the string to split on.
 * @return a newly malloc-ed string array.
 */
sf_SplitString* sf_split_string(char *string, char *substring);

/**
 * Split a string similar to String.split in java.
 * This modifies the original string.
 * NOTE: Does not work for string literals - will cause segfault.
 * @param string the source string to split.
 * @param substring the string to split on.
 * @return an array of string as a SplitString object.
 */
sf_SplitString* sf_split_string_inplace(char *string, char *substring);

/**
 * Free a string split created using split_string
 * @param split the data to be freed.
 */
void sf_free_split_string(sf_SplitString *split);

#endif
