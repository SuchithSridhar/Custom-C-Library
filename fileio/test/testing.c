#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../fileio.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Invalid call to test file. Pass test file and command as command line arg.\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[2], "readline") == 0) {
        FILE *f = fopen(argv[1], "r");

        if (f == NULL) {
            fprintf(stderr, "File not found.\n");
            return EXIT_FAILURE;
        }

        fio_DataRead *fio_data;
        while (true) {
            fio_data = fio_read_line(f);
            if (fio_data->status != FIO_SUCCESS) break;
            printf(
                "=%s=%d=%c=\n",
                fio_data->lines[0],
                fio_data->str_lens[0],
                fio_data->status
            );
            fio_free_DataRead(fio_data);
        }
    } else if (strcmp(argv[2], "readfile") == 0) {
        FILE *f = fopen(argv[1], "r");

        if (f == NULL) {
            fprintf(stderr, "File not found.\n");
            return EXIT_FAILURE;
        }

        fio_DataRead *fio_data;
        fio_data = fio_read_file(f);
        if (fio_data->status == FIO_SUCCESS) {
            printf(
                "=%s=%d=%c=\n",
                fio_data->lines[0],
                fio_data->str_lens[0],
                fio_data->status
            );
            fio_free_DataRead(fio_data);
        }
    } else {
        fprintf(stderr, "Invalid command to program.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
