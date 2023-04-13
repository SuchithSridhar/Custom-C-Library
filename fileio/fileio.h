#ifndef _FILE_IO_H
#define _FILE_IO_H

#include <stdio.h>

#define FIO_NULL_ERR 'n'
#define FIO_MEM_ERR 'm'
#define FIO_EOF EOF
#define FIO_SUCCESS 's'


/**
 * Functions in the fileio library use
 * this type to report errors.
 */
typedef char FIO_STATUS;


/**
 * Read string until the end of the line or file.
 * 
 */
char* read_line(FILE *stream, int *str_len, FIO_STATUS *status);

#endif
