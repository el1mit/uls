#include "../inc/uls.h"

static int max_name_len(t_manager **files) {
    int max = 0;
    int temp = 0;

    for (int i = 0; files[i]; i++) {
        temp = mx_strlen(files[i]->name);

        if (temp > max) {
            max = temp;
        }
    }

    if (max % 8 == 0) {
        max += 8;
    }
    else {
        max = 8 - (max % 8) + max;
    }

    return max;
}

static void tab_printer(int len, int max_len, t_flags* flags) {
    int count = 0;
    int p = max_len - len;

    if(flags->G) {

        for (int i = len; i < (max_len / 2) + 1; i++) {
            mx_printchar(' ');
        }

    }
    else {

        if (p % 8 != 0) {
            count = (p / 8) + 1;
        }
        else {
            count = p / 8;
        }

        for (int i = 0; i < count; i++) {
            mx_printchar('\t');
        }
    }
}

static void column_printer(t_manager **files, int rows, int num, int max_len, t_flags* flags) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; i + j < num; j += rows) {
            mx_printstr(files[i + j]->name);

            if (files[i + j + 1] && (i + j + rows < num)) {
                tab_printer(mx_strlen(files[i + j]->name), max_len, flags);
            }
        }

        if (i != rows - 1) {
            mx_printchar('\n');
        }
    }
}

static void clean_output(t_manager **files, int max_len, int win_col, t_flags* flags) {
    int rows = 0, cols = 0, count = 0;

    if ((win_col / max_len) != 0) {
        cols = win_col / max_len;
    }
    else {
        cols++;
    }

    for (;files[count];) {
        count++;
    }

    if (max_len * cols > win_col && cols != 1) {
        cols--;
    }
    if (count * max_len > win_col) {
        rows = count / cols;

        if (rows == 0 || count % cols != 0) {
            rows++;
        }
        column_printer(files, rows, count, max_len, flags);
    } else {
        for (int i = 0; files[i]; i++) {
            if (flags->G) {

                struct stat buf = files[i]->statistic;
                
                if (S_ISDIR(buf.st_mode)) {
                    mx_printstr(CL_BLUE);
                }
                else if (buf.st_mode & S_IXUSR) {
                    mx_printstr(CL_RED);
                }
                else if (S_ISSOCK(buf.st_mode)) {
                    mx_printstr(CL_GREEN);
                }
                else if (S_ISFIFO(buf.st_mode)) {
                    mx_printstr(CL_BROWN);
                }
                else if (S_ISLNK(buf.st_mode)) {
                    mx_printstr(CL_MAGENTA);
                }
                else if (S_ISBLK(buf.st_mode)) {
                    mx_printstr(CL_BLUE);
                    mx_printstr(CL_BOLD_CYAN);
                }
                else if (S_ISCHR(buf.st_mode)) {
                    mx_printstr(CL_BLUE);
                    mx_printstr(CL_BOLD_BROWN);
                }
                else if (buf.st_mode & S_ISUID) {
                    mx_printstr(CL_BLACK);
                    mx_printstr(CL_BOLD_RED);
                }
                else if (buf.st_mode & S_ISGID) {
                    mx_printstr(CL_BLACK);
                    mx_printstr(CL_BOLD_CYAN);
                }
                else if (buf.st_mode & S_ISVTX) {
                    mx_printstr(CL_BLACK);
                    mx_printstr(CL_BOLD_GREEN);
                }

            }

            mx_printstr(files[i]->name);
            if (flags->G) {
                mx_printstr(CL_END);
            }
            
            if (flags->F) {
                struct stat buf = files[i]->statistic;
                if (buf.st_mode & S_IFDIR) {
                    mx_printstr("/");
                }
                else if (buf.st_mode & S_IXUSR) {
                    mx_printstr("*");
                }
                else if (buf.st_mode & S_IFLNK) {
                    mx_printstr("@");
                }
                else if (buf.st_mode & S_IFSOCK) {
                    mx_printstr("=");
                }
                else if (buf.st_mode & S_IFIFO) {
                    mx_printstr("|");
                }
            }

            if (files[i + 1]) {
                tab_printer(mx_strlen(files[i]->name), max_len, flags);
            }
        }
    }

    mx_printchar('\n');
}

void print_clean(t_manager **files, t_flags* flags) {
    if (files == NULL) {
        return;
    }

    struct winsize window;
    int word_max_len = max_name_len(files);

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

    if (isatty(1)) {
        clean_output(files, word_max_len, window.ws_col, flags);
    }
    else {
        clean_output(files, word_max_len, 80, flags);
    }
}

