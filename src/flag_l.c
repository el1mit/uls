#include "../inc/uls.h"

void find_max(t_manager** text, int* blocks, int* max_size, int* max_links, int* max_usname, int* max_grname) {

    for (int i = 0; text[i] != NULL; i++) {
        
        struct stat buf = text[i]->statistic;
        int b = buf.st_blocks;
        *blocks += b;

        // max len of string of links
        int links = buf.st_nlink;
        if (mx_strlen(mx_itoa(links)) > * max_links) {
            *max_links = mx_strlen(mx_itoa(links));
        }

        // max len of string of username
        struct passwd* u = getpwuid(buf.st_uid);

        if (u != NULL) {
            if (mx_strlen(u->pw_name) > * max_usname) {
                *max_usname = mx_strlen(u->pw_name);
            }
        }
        else {
            char* at = mx_itoa(buf.st_uid);
            if (mx_strlen(at) > * max_usname) {
                *max_usname = mx_strlen(at);
            }
        }

        
       
        // max len of string of group's name
        struct group* g = getgrgid(buf.st_gid);

        if(g != NULL) {
            if (mx_strlen(g->gr_name) > *max_grname) {
                *max_grname = mx_strlen(g->gr_name);
            }
        }  
        else {
            
            char* at = mx_itoa(buf.st_gid);
            if (mx_strlen(at) > *max_grname) {
                *max_grname = mx_strlen(at);
            }
        } 
       
        // max len of string of size
        int i = buf.st_size;
        if (mx_strlen(mx_itoa(i)) > * max_size) {
            *max_size = mx_strlen(mx_itoa(i));
        }

    }

}

void flag_l(t_manager** text, t_flags* flags) {

    int blocks = 0, max_size = 0, max_links = 0, max_usname = 0, max_grname = 0;
    find_max(text, &blocks, &max_size, &max_links, &max_usname, &max_grname);

    mx_printstr("total ");
    mx_printint(blocks);
    mx_printstr("\n");

    for (int i = 0; text[i] != NULL; i++) {

        struct stat buf = text[i]->statistic;

        if ((buf.st_mode & S_IFDIR)) {
            mx_printstr("d");
        }
        else {
            mx_printstr("-");
        }

        // user
        if ((buf.st_mode & S_IRUSR)) {
            mx_printstr("r");
        }
        else {
            mx_printstr("-");
        }

        if ((buf.st_mode & S_IWUSR)) {
            mx_printstr("w");
        }
        else {
            mx_printstr("-");
        }

        if ((buf.st_mode & S_IXUSR)) {
            mx_printstr("x");
        }
        else {
            mx_printstr("-");
        }

        // group
        if ((buf.st_mode & S_IRGRP)) {
            mx_printstr("r");
        }
        else {
            mx_printstr("-");
        }

        if ((buf.st_mode & S_IWGRP)) {
            mx_printstr("w");
        }
        else {
            mx_printstr("-");
        }

        if ((buf.st_mode & S_IXGRP)) {
            mx_printstr("x");
        }
        else {
            mx_printstr("-");
        }

        // others

        if ((buf.st_mode & S_IROTH)) {
            mx_printstr("r");
        }
        else {
            mx_printstr("-");
        }

        if ((buf.st_mode & S_IWOTH)) {
            mx_printstr("w");
        }
        else {
            mx_printstr("-");
        }

        if ((buf.st_mode & S_IXOTH)) {
            mx_printstr("x");
        }
        else {
            mx_printstr("-");
        }

        mx_printstr("  ");

        // links

        int t = buf.st_nlink;

        for (int j = mx_strlen(mx_itoa(t)); j < max_links; j++) {
            mx_printstr(" ");
        }

        mx_printint(t);
        mx_printstr(" ");

        // name of user

        struct passwd* u = getpwuid(buf.st_uid);

        if (u != NULL) {
            for (int j = mx_strlen(u->pw_name); j < max_usname; j++) {
                mx_printstr(" ");
            }
            mx_printstr(u->pw_name);
            mx_printstr("  ");
        }
        else {
            char* at = mx_itoa(buf.st_uid);
            for (int j = mx_strlen(at); j < max_usname; j++) {
                mx_printstr(" ");
            }
            mx_printint(buf.st_uid);
        }

        

        // name of group
        struct group* g = getgrgid(buf.st_gid);

        if(g != NULL) {

            for (int j = mx_strlen(g->gr_name); j < max_grname; j++) {
                mx_printstr(" ");
            }
            mx_printstr(g->gr_name);
        }
        else {
          
            char* at = mx_itoa(buf.st_gid);
            for (int j = mx_strlen(at); j < max_grname; j++) {
                mx_printstr(" ");
            }
            mx_printint(buf.st_gid);
        }
        

        mx_printstr("  ");

        // size
        int size = buf.st_size;
        char* size_text = mx_itoa(size);

        for (int j = mx_strlen(size_text); j < max_size; j++) {
            mx_printstr(" ");
        }
        mx_printstr(size_text);

        mx_printstr(" ");


        // time
        time_t *m_time = &buf.st_mtime;
        time_t *c_time = &buf.st_ctime;
        time_t *a_time = &buf.st_atime;
        
        if (flags->c) {
            m_time = c_time;
        }
        if (flags->u) {
            m_time = a_time;
        }

        char *str = ctime(m_time);
        int i_i = 0;
        if (time(NULL) - buf.st_mtime < 15811200) {
            for (i_i = 4; i_i < 16; i_i++) {
                mx_printchar(str[i_i]);
            }
        }
        else {
            for (i_i = 4; i_i < 11; i_i++) {
                mx_printchar(str[i_i]);
            }

            for (i_i = 19; i_i < 24; i_i++) {
                mx_printchar(str[i_i]);
            }
        }
        mx_printstr(" ");

        // name
        if (flags->G) {

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

        mx_printstr(text[i]->name);
        if (flags->G) {
            mx_printstr(CL_END);
        }

        if (flags->F) {

            if (S_ISDIR(buf.st_mode)) {
                mx_printstr("/");
            }
            else if (buf.st_mode & S_IXUSR) {
                mx_printstr("*");
            }
            else if (S_ISLNK(buf.st_mode)) {
                mx_printstr("@");
            }
            else if (S_ISSOCK(buf.st_mode)) {
                mx_printstr("=");
            }
            else if (S_ISFIFO(buf.st_mode)) {
                mx_printstr("|");
            }
        }

        mx_printstr("\n");
    }

}

