#include "../inc/uls.h"

void clean_dirs(t_manager ***inp) {
    t_manager **to_del = *inp;

    for (int i = 0; to_del[i]; i++) {
        mx_strdel(&to_del[i]->name);
        mx_strdel(&to_del[i]->path);

        if (to_del[i]->error) {
            mx_strdel(&to_del[i]->error);
        }
        if (to_del[i]->open != NULL) {
            clean_dirs(&to_del[i]->open);
        }

        free(to_del[i]);
        to_del[i] = NULL;
    }

    free(*inp);
    *inp = NULL;
}

static void clean_dirs_list(t_manager ***to_del, t_manager **dirs) {
    t_manager **temp = *to_del;

    for (int i = 0; temp[i]; i++) {
        mx_strdel(&temp[i]->name);
        mx_strdel(&temp[i]->path);

        if (temp[i]->error) {
            mx_strdel(&temp[i]->error);
        }

        free(temp[i]);
        temp[i] = NULL;
    }

    free(*to_del);
    *to_del = dirs;
}

static void new_dir(t_manager ***dirs, t_manager ***inp) {
    int n_dir = 0;

    for (int i = 0; (*inp)[i]; i++) {
        if ((*inp)[i]->error == NULL) {
            if (S_ISDIR((*inp)[i]->statistic.st_mode) &&
                mx_strcmp((*inp)[i]->name, ".") != 0 &&
                mx_strcmp((*inp)[i]->name, "..") != 0) {
                n_dir++;
            }
        }
    }

    if (n_dir > 0) {
        *dirs = malloc((n_dir + 1) * sizeof(t_manager *));
    }
}

void clean_files(t_manager ***to_del, t_flags *flags) {
    t_manager **dirs = NULL;
    int n_dir = 0;

    new_dir(&dirs, to_del);

    for (int i = 0; (*to_del)[i] != NULL; i++) {
        if ((*to_del)[i]->error == NULL) {
            if (S_ISDIR((*to_del)[i]->statistic.st_mode) &&
                mx_strcmp((*to_del)[i]->name, ".") != 0 &&
                mx_strcmp((*to_del)[i]->name, "..") != 0) {
                dirs[n_dir++] = add_file_node((*to_del)[i]);
                dirs[n_dir] = NULL;
            }
        }
    }

    flags->is_files = 1;
    clean_dirs_list(to_del, dirs);
}

