#ifndef ULS_H
#define ULS_H

#include "../libmx/inc/libmx.h"

#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/xattr.h>
#include <sys/ioctl.h>

#define CL_BLACK "\033[0;30m"
#define CL_RED "\033[0;31m"
#define CL_GREEN "\033[0;32m"
#define CL_BROWN "\033[0;33m"
#define CL_BLUE "\033[0;34m"
#define CL_MAGENTA "\033[0;35m"

#define CL_BOLD_RED "\033[41m"
#define CL_BOLD_GREEN "\033[42m"
#define CL_BOLD_BROWN "\033[43m"
#define CL_BOLD_BLUE "\033[44m"
#define CL_BOLD_MAGENTA "\033[45m"
#define CL_BOLD_CYAN "\033[46m"

#define CL_END "\033[0m"

typedef struct s_flags {
    int l;
    int a;
    int t;
    int r;
    int c;
    int u;
    int S;
    int G;
    int A;
    int R;
    int F;
    int is_files;
}              t_flags;

typedef struct s_manager {
    char *path;
    char *name;
    char *error;
    struct stat statistic;
    struct s_manager **open;
}              t_manager;

typedef struct s_obj_counter {
    int dirs_count;
    int files_count;
    int errors_count;
    int i;
}              t_obj_counter;

void usage(void);
void illegal_opt(char opt);

void check_flags(t_flags **flags, char **argv, int *c);
t_manager **fill_file_manager(char **files_name, int files_count);
t_manager *add_node(char *data);
t_manager *add_file_node(t_manager *node);
t_manager *add_named_node(char *name, char *path);
void count_obj(t_manager ***all_files, t_manager ***dirs, t_manager ***files, t_manager ***errors);
void arrange_obj(t_manager ***all_files, t_manager ***dirs, t_manager ***files, t_manager ***errors, t_obj_counter *counter);


char** get_files(int argc, char** argv, int counter, int* files_count);
void sort_files(char** arr, int size);
void sort_obj(t_manager ***inp, t_flags** flags, char** argv);

void print_menu(t_manager*** files, t_flags* flags, char** argv);
void print_errors(t_manager ***errors);
void print_clean(t_manager** files, t_flags* flags);
void print_dirs(t_manager*** dirs, t_flags* flags, t_obj_counter* counter, char** argv);
void flag_l(t_manager** text, t_flags* flags);

void clean_dirs(t_manager ***inp);
void clean_files(t_manager ***to_del, t_flags *flags);

#endif // ULS_H
