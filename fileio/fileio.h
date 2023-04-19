#ifndef _FILE_IO_H
#define _FILE_IO_H

#include <stdio.h>

/* One of the params were NULL. */
#define FIO_NULL_ERR 'n'

/* A memory error, such as a failed malloc. */
#define FIO_MEM_ERR 'm'

/* The only character present is the EOF character. */
#define FIO_EOF 'e'

/* The operation was successful. */
#define FIO_SUCCESS 's'


/**
 * Functions in the fileio library use
 * this type to report errors.
 */
typedef char fio_Status;


/**
 * Read string until the end of the line or file.
 * @param stream a FILE stream to read data from.
 * @param str_len this is a pointer where the length of
 *        the read in string is stored when it's not NULL.
 * @param status this is a pointer to where the status of
 *        of the operation is stored when it's not NULL.
 * @return the string that is read in.
 */
char* fio_read_line(FILE *stream, int *str_len, fio_Status *status);

/**
 * TODO: Complete this function and docs.
 */
char* fio_read_lines(FILE *stream, int *str_len, fio_Status *status);

/**
 * Read string until end of file.
 * @param stream a FILE stream to read data from.
 * @param str_len this is a pointer where the length of
 *        the read in string is stored when it's not NULL.
 * @param status this is a pointer to where the status of
 *        of the operation is stored when it's not NULL.
 * @return the string that is read in.
 */
char* fio_read_file(FILE *stream, int *str_len, fio_Status *status);

/**
 * Write a line to a file.
 * The newline character isn't added automatically.
 * @param stream a FILE stream to write data to.
 * @param string the string that is to be written.
 * @return The status of the operation. 
 */
fio_Status fio_write_line(FILE *stream, char *string);

/**
 * Write an array of string to a file. The delimiter
 * string is appended between all pairs of strings.
 * @param stream a FILE stream to write data to.
 * @param str_arr the array of string to be written.
 * @param arr_len the length of the string array.
 * @param delimiter the delimiter to add between 2 items in the array.
 *        If NULL, delimiter will be set to the empty string.
 * @return The status of the operation. 
 */
fio_Status fio_write_lines(FILE *stream, char **str_arr, int arr_len, char* delimiter);

/**
 * Write a string to a file.
 * The newline character isn't added automatically.
 * @param stream a FILE stream to write data to.
 * @param string the string that is to be written.
 * @return The status of the operation. 
 */
fio_Status fio_write_file(FILE *stream, char *string);

#endif
