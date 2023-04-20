# Library Of File I/O Operations

A library of file I/O operations that I commonly perform.  
All functions and types in this file are prefixed with `_fio`.

### Errors

All errors in this file are reported using the `fio_Status` type.

| Value | Description |
| ----- | ----------- |
| FIO_NULL_ERR | One of the parameters were `NULL`. |
| FIO_MEM_ERR | A memory error, such as a failed `malloc`. |
| FIO_EOF | The only character present in the file is the End-of-file. |
| FIO_SUCCESS | The operation was successful. |


### Function Definitions

- **fio_read_line**
```c
char* fio_read_line(FILE *stream, int *str_len, fio_Status *status);
```
Read a line (a string that ends with `\n` or `EOF`) from a file stream.

- **fio_read_lines**
```c
char* fio_read_lines(FILE *stream, int *str_len, fio_Status *status);
```
Read all lines in the file stream as an array of strings.

- **fio_read_file**
```c
char* fio_read_file(FILE *stream, int *str_len, fio_Status *status);
```
Read an entire file as a single string (read till `EOF`).

- **fio_write_line**
```c
fio_Status fio_write_line(FILE *stream, char *string);
```
Write a line to a file stream (`\n` is not appended to the end).


- **fio_write_lines**
```c
fio_Status fio_write_lines(FILE *stream, char **str_arr, int arr_len, char* delimiter);
```
Write an array of lines/string separate by the delimiter provided to a file.


- **fio_write_file**
```c
fio_Status fio_write_file(FILE *stream, char *string);
```
Write a string to a file stream.
