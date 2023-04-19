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
        char *string;
        FILE *f = fopen(argv[1], "r");

        if (f == NULL) {
            fprintf(stderr, "File not found.\n");
            return EXIT_FAILURE;
        }

        int length;
        fio_Status status;
        while (true) {
            string = fio_read_line(f, &length, &status);
            if (string == NULL) break;
            printf("=%s=%d=%c=\n", string, length, status);
            free(string);
        }
    } else if (strcmp(argv[2], "readfile") == 0) {
        char *string;
        FILE *f = fopen(argv[1], "r");

        if (f == NULL) {
            fprintf(stderr, "File not found.\n");
            return EXIT_FAILURE;
        }

        int length;
        fio_Status status;
        string = fio_read_file(f, &length, &status);
        if (string != NULL) {
            printf("=%s=%d=%c=\n", string, length, status);
            free(string);
        }
    } else {
        fprintf(stderr, "Invalid command to program.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
