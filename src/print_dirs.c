#include "../inc/uls.h"

bool is_A_flag(char *str, t_flags *flags) {
    if (!flags->A || !(mx_strcmp(str, ".")) || !(mx_strcmp(str, ".."))) {
        return false;
    }
    return true;
}

bool is_a_flag(char *str, t_flags *flags) {
    if (!(mx_strcmp(str, ".")) || !(mx_strcmp(str, ".."))) {
        if (!flags->a) {
            return 0;
        }
        return 1;
    }
    if (str[0] == '.' && flags->a) {
        return 1;
    }

    return 0;
}

static int files_count(t_manager **dir, t_flags *flags) {
    int count = 0;
    t_manager *dir_copy = *dir;
    DIR *dir_p;
    struct dirent *reader;

    if (S_ISDIR(dir_copy->statistic.st_mode) || S_ISLNK(dir_copy->statistic.st_mode)) {
        if ((dir_p = opendir(dir_copy->path)) != NULL) {
            while((reader = readdir(dir_p)) != NULL) {
                if (reader->d_name[0] != '.' || is_a_flag(reader->d_name, flags) || is_A_flag(reader->d_name, flags)) {
                    count++;
                }
            }
            closedir(dir_p);
        }
        else {
            (*dir)->error = mx_strdup(strerror(errno));
            return -1;
        }
    }
    return count;
}

static void check_errors_and_print(t_manager** dirs, t_flags* flags, t_obj_counter *counter, char** argv) {
    if ((*dirs)->open != NULL) {
        print_menu(&(*dirs)->open, flags, argv);

        if (flags->R == 1) {
            flags->is_files = 1;
            clean_files(&(*dirs)->open, flags);

            if ((*dirs)->open) {
                mx_printchar('\n');
                print_dirs(&(*dirs)->open, flags, counter, argv);
            }
        }

    }
    else if ((*dirs)->error != NULL) {
        mx_printerr("uls: ");
        mx_printerr((*dirs)->path);
        mx_printerr(": ");
        mx_printerr((*dirs)->error);
        mx_printerr("\n");
    }
}

static void output_dirs(t_manager*** dirs, t_flags* flags, t_obj_counter* counter, char** argv) {
    if (*dirs) {
        for (int i = 0; (*dirs)[i]; i++) {
            if (counter->dirs_count > 1 || counter->files_count > 0 || counter->errors_count > 0) {
                mx_printstr((*dirs)[i]->path);
                mx_printstr(":\n");
            }

            if (flags->is_files == 1) {
                if ((*dirs)[i]->path[0] == '/' && (*dirs)[i]->path[1] == '/') {
                    mx_printstr(&(*dirs)[i]->path[1]);
                }
                else {
                    mx_printstr((*dirs)[i]->path);
                }

                mx_printchar(':');
                mx_printchar('\n');
            }

            check_errors_and_print(&(*dirs)[i], flags, counter, argv);

            if ((*dirs)[i + 1]) {
                mx_printchar('\n');
            }
        }

        clean_dirs(dirs);
    }
}

void print_dirs(t_manager*** dirs, t_flags* flags, t_obj_counter* counter, char** argv) {
    DIR* dir;
    struct dirent* reader;
    int count = 0;

    for (int i = 0; (*dirs)[i]; i++) {
        count = files_count(&(*dirs)[i], flags);

        if (count > 0) {
            (*dirs)[i]->open = (t_manager**)malloc((count + 1) * sizeof(t_manager*));

            if ((dir = opendir((*dirs)[i]->path)) != NULL) {
                for (count = 0; (reader = readdir(dir)) != NULL;) {
                    if (reader->d_name[0] != '.' || is_a_flag(reader->d_name, flags) || is_A_flag(reader->d_name, flags)) {
                        (*dirs)[i]->open[count++] = add_named_node(reader->d_name, (*dirs)[i]->path);
                    }
                }
                (*dirs)[i]->open[count] = NULL;
            }
            closedir(dir);
        }
    }
    output_dirs(dirs, flags, counter, argv);
}

