#include <stdlib.h>
#include <stdio.h>

#include "../fileio.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Invalid call to test file. Pass test file as command line arg.\n");
        return EXIT_FAILURE;
    }

    char *string;
    FILE *f = fopen(argv[1], "r");

    if (f == NULL) {
        fprintf(stderr, "File not found.\n");
        return EXIT_FAILURE;
    }

    while (1) {
        string = read_line(f, NULL, NULL);
        if (string == NULL) break;
        printf("==%s==\n", string);
        free(string);
    }
    return EXIT_SUCCESS;
}
