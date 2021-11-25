#include "../inc/uls.h"

char **get_files(int argc, char **argv, int counter, int *files_count) {
    char **files = NULL;

    if (counter == argc) {
        files = (char **)malloc(2 * sizeof(char *));
        files[0] = mx_strdup(".");
        files[1] = NULL;
        *files_count = 2;
    }
    else {
        int i = counter;
        while (argv[i]) {
            i++;
        }

        files = (char **)malloc((i - counter + 1) * sizeof(char *));

        for (i = 0; argv[counter]; counter++, i++) {
            files[i] = mx_strdup(argv[counter]);
        }
        files[i] = NULL;
        *files_count = i + 1;
    }

    return files;
}


