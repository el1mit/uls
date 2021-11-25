#include "../inc/uls.h"

void illegal_opt(char opt) {
    mx_printerr("uls: illegal option -- ");
    write(2, &opt, 1);
    write(2, "\n", 1);
    usage();
}

