#include "../inc/uls.h"

static t_obj_counter *obj_counter_init() {
    t_obj_counter *new = (t_obj_counter *)malloc(sizeof(t_obj_counter));

    new->dirs_count = 0;
    new->files_count = 0;
    new->errors_count = 0;
    new->i = 0;

    return new;
}

static t_flags *flags_init() {
    t_flags *new = (t_flags *)malloc(sizeof(t_flags));

    new->l = 0;
    new->a = 0;
    new->t = 0;
    new->r = 0;
    new->u = 0;
    new->c = 0;
    new->S = 0;
    new->A = 0;
    new->R = 0;
    new->G = 0;
    new->F = 0;
    return new;
}

static void print_one(t_manager **files) {
    for (int i = 0; files[i]; i++) {
        mx_printstr(files[i]->name);
        mx_printchar('\n');
    }   
}

void print_menu(t_manager ***files, t_flags* flags, char** argv) {

    sort_obj(&(*files), &flags, argv);
    if (flags->l) {
        flag_l(*files, flags);
    }
    if (!flags->l && isatty(1)) {
        print_clean(*files, flags);
    }
    if(!isatty(1) && ! flags->l) {
        print_one(*files);
    }
}

int main(int argc, char *argv[]) {
    t_flags *flags = flags_init();
    t_obj_counter *obj_counter = obj_counter_init();
    int counter = 1;
    int files_count = 0;
    check_flags(&flags, argv, &counter);


    char **files_names = get_files(argc, argv, counter, &files_count);

    t_manager **all_files = fill_file_manager(files_names, files_count);
    mx_del_strarr(&files_names);

    t_manager **dirs = NULL;
    t_manager **files = NULL;
    t_manager **errors = NULL;

    count_obj(&all_files, &dirs, &files, &errors);
    arrange_obj(&all_files, &dirs, &files, &errors, obj_counter);

    if (obj_counter->errors_count > 0) {
        sort_obj(&errors, &flags, argv);
        print_errors(&errors);
    }

    if (obj_counter->files_count > 0) {
        print_menu(&files, flags, argv);
        if (obj_counter->dirs_count > 0) {
            mx_printchar('\n');
        }
        clean_dirs(&files);
    }

    if (obj_counter->dirs_count > 0) {
        print_dirs(&dirs, flags, obj_counter, argv);
    }
    
    free(flags);
    flags = NULL;

    free(obj_counter);
    obj_counter = NULL;

    return 0;
}

