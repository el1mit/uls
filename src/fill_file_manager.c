#include "../inc/uls.h"

t_manager **fill_file_manager(char **files_name, int files_count) {
    t_manager **files = (t_manager **)malloc(files_count * sizeof(t_manager *));

    int i = 0;
    for (;files_name[i]; i++) {
        files[i] = add_node(files_name[i]);
    }

    files[i] = NULL;
    return files;

}


