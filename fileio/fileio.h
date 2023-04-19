#ifndef _FILE_IO_H
#define _FILE_IO_H

#include <stdio.h>

#define FIO_NULL_ERR 'n'
#define FIO_MEM_ERR 'm'
#define FIO_EOF 'e'
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
 * Read string until end of file.
 * @param stream a FILE stream to read data from.
 * @param str_len this is a pointer where the length of
 *        the read in string is stored when it's not NULL.
 * @param status this is a pointer to where the status of
 *        of the operation is stored when it's not NULL.
 * @return the string that is read in.
 */
char* fio_read_file(FILE *stream, int *str_len, fio_Status *status);

#endif
