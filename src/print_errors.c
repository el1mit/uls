#include "../inc/uls.h"

void print_errors(t_manager ***errors) {
    for (int i = 0; (*errors)[i]; i++) {
        mx_printerr("uls: ");
        mx_printerr((*errors)[i]->name);
        mx_printerr(": ");
        mx_printerr((*errors)[i]->error);
        mx_printerr("\n");

        mx_strdel(&(*errors)[i]->name);
        mx_strdel(&(*errors)[i]->path);
        mx_strdel(&(*errors)[i]->error);

        free((*errors)[i]);
        (*errors)[i] = NULL;
    }

    free(*errors);
    *errors = NULL;
}

