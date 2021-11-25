#include "../inc/uls.h"

void count_obj(t_manager ***all_files, t_manager ***dirs, t_manager ***files, t_manager ***errors) {
    int n_files = 0;
    int n_dirs = 0;
    int n_errors = 0;

    for (int i = 0; (*all_files)[i]; i++) {

        if ((*all_files)[i]->error == NULL) {
            if (S_ISDIR((*all_files)[i]->statistic.st_mode) == 0) {
                n_files++;
            }
            else
                n_dirs++;
        }
        else {
            n_errors++;
        }
    }

    if (n_dirs > 0) {
        *dirs = malloc((n_dirs + 1) * sizeof(t_manager));
    }
    if (n_files > 0) {
        *files = malloc((n_files + 1) * sizeof(t_manager));
    }
    if (n_errors > 0) {
        *errors = malloc((n_errors + 1) * sizeof(t_manager));
    }
}


