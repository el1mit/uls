#include "../inc/uls.h"

static bool add_flag(t_flags** flags, char flag) {
    if (flag == 'l') {
        (*flags)->l = 1;
        return true;
    }
    else if (flag == 'a') {
        (*flags)->a = 1;
        return true;
    }
    else if (flag == 't') {
        (*flags)->t = 1;
        return true;
    }
    else if (flag == 'r') {
        (*flags)->r = 1;
        return true;
    }
    else if (flag == 'A') {
        (*flags)->A = 1;
        return true;
    }
    else if (flag == 'R') {
        (*flags)->R = 1;
        return true;
    }
    else if (flag == 'G') {
        (*flags)->G = 1;
        return true;
    }
    else if (flag == 'F') {
        (*flags)->F = 1;
        return true;
    }
    else if (flag == 'u' || flag == 'c' || flag == 'S') {
        return true;
    }
    else {
        return false;
    }
}


void check_flags(t_flags **flags, char **argv, int *c) {

    for (; argv[(*c)]; (*c)++) {
        if (argv[(*c)][0] == '-') {
            if (argv[(*c)][1] == '-') {
                (*c)++;
                break;
            }
            if (argv[(*c)][1] == '\0') {
                break;
            }

            for (int i = 1; argv[(*c)][i]; i++) {
                if (!add_flag(flags, argv[(*c)][i])) {
                    illegal_opt(argv[(*c)][i]);
                }
            }
        }
        else {
            break;
        }
    }
}


