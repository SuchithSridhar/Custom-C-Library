#ifndef _STRING_FUNCTIONS_H
#define _STRING_FUNCTIONS_H

#include <stdbool.h>


/**
 * Remove a set of characters from the start
 * and end of a string. A new allocated string is returned.
 * @param string a string with all the character that are to be removed.
 * @return a new string allocated on the heap having trimmed $c.
 */
char* trim_chars(char *string, char *chars);

/**
 * Remove all white-space characters from the start
 * and end of a string. A new allocated string is retuned.
 * @return a new string allocated on the heap having trimmed $c.
 */
char* trim_whitespace(char *string);

/**
 * Check if a given character is in a string.
 * @param string the string to look for the character in.
 * @param c the character to look for.
 * @return true if the character was found, else false.
 */
bool char_in_str(char* string, char c);

/**
 * Check is a string is contained within another string.
 * @param string the source string to check within.
 * @param substring the substring to look for. 
 * @return true if the substring is contained in the string,
 *         else false.
 */
bool is_substring(char* string, char *substring);

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
char* get_substring(char *string, int start, int stop, int step);

/**
 * Convert a string to upper case.
 * The returned string is malloc-ed on the heap.
 * @param string the string to be converted.
 * @return string in upper case, NULL if failed.
 */
char* to_uppercase(char* string);

/**
 * Convert a string to lower case.
 * The returned string is malloc-ed on the heap.
 * @param string the string to be converted.
 * @return string in lower case, NULL if failed.
 */
char* to_lowercase(char* string);

/**
 * Get the index of a substring.
 * -1 if the substring is not present.
 *  @param string the source string to check in.
 *  @param substring the substring to look for.
 *  @param start the position to start at.
 *  @return the index of the substring or -1 if not present.
 */
int index_of(char *string, char *substring, int start);

/**
 * Get the index of a substring starting from the end of the string.
 * -1 if the substring is not present.
 *  @param string the source string to check in.
 *  @param substring the substring to look for.
 *  @param start the position to start at.
 *  @return the index of the substring or -1 if not present.
 */
int index_of_reverse(char *string, char *substring, int start);

/**
 * Split a string similar to String.split in java.
 * @param string the source string to split.
 * @param substring the string to split on.
 * @return a newly malloc-ed string array.
 */
char** split_string(char *string, char *substring);

/**
 * Split a string similar to String.split in java.
 * This modifies the original string.
 * @param string the source string to split.
 * @param substring the string to split on.
 * @return an array of string 
 */
char** split_string_inplace(char *string, char *substring);

/**
 * Free a string split created using split_string 
 * @param split_array the array of string to free.
 */
void free_split_string(char** split_array);

#endif
