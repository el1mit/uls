#include "../inc/uls.h"

void sort_files(char **arr, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
            if (mx_strcasecmp(arr[i], arr[j]) > 0) {
				char *temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

