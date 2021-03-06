#include "../inc/libmx.h"

int mx_count_substr(const char* str, const char* sub) {
    if (!str  || !sub) {
        return -1;
    }

    int i = 0;

    if (mx_strlen(str) >= mx_strlen(sub)) {
        while (*str) {
            if (!mx_strncmp((char*)str, (char*)sub, mx_strlen(sub))) {
                i++;
            }
            str++;
        }
    }
    return i;
}

