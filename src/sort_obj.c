#include "../inc/uls.h"

void swap(t_manager** t1, t_manager** t2) {

	t_manager* temp = *t1;
	*t1 = *t2;
	*t2 = temp;

}

void sort_obj(t_manager ***inp, t_flags** flags, char** argv) {

    t_manager **text = *inp;
	char* str_argv = NULL;

	for (int i = 1; argv[i] != NULL; i++) {
		if (argv[i][0] == '-') {
			str_argv = mx_strjoin(str_argv, argv[i]);
		}
	}

	bool was_here = false;

	if (str_argv != NULL) {
		for (int k = 0; str_argv[k] != '\0'; k++) {

			for (int i = 0; text[i + 1] != NULL; i++) {

				for (int j = i + 1; text[j] != NULL; j++) {

					if (str_argv[k] == 'c') {
						(*flags)->c = 1;
						(*flags)->u = 0;

						if (((*flags)->l && !(*flags)->t) || ((*flags)->S && !(*flags)->l) || !(*flags)->t) {
							continue;
						}

						struct stat buf1 = text[i]->statistic;
						struct stat buf2 = text[j]->statistic;

						long int time1 = buf1.st_ctimespec.tv_sec;
						long int time2 = buf2.st_ctimespec.tv_sec;

						if (time1 < time2 || (time1 == time2 && mx_strcmp(text[i]->name, text[j]->name) > 0)) {
							swap(&text[i], &text[j]);
						}

						was_here = true;

					}

					if (str_argv[k] == 'u') {
						(*flags)->c = 0;
						(*flags)->u = 1;

						if (((*flags)->l && !(*flags)->t) || ((*flags)->S && !(*flags)->l) || !(*flags)->t) {
							continue;
						}

						struct stat buf1 = text[i]->statistic;
						struct stat buf2 = text[j]->statistic;

						long int time1 = buf1.st_atimespec.tv_sec;
						long int time2 = buf2.st_atimespec.tv_sec;

						if (time1 < time2 || (time1 == time2 && mx_strcmp(text[i]->name, text[j]->name) > 0)) {
							swap(&text[i], &text[j]);
						}

						was_here = true;

					}

					if (str_argv[k] == 'S') {

						struct stat buf1 = text[i]->statistic;
						struct stat buf2 = text[j]->statistic;

						int size1 = buf1.st_size;
						int size2 = buf2.st_size;

						if (size1 < size2 || (buf1.st_size == buf2.st_size && mx_strcmp(text[i]->name, text[j]->name) > 0)) {
							swap(&text[i], &text[j]);
						}
						(*flags)->S = 1;
						was_here = true;

					}

					if (!(*flags)->u && !(*flags)->c && (*flags)->t) {

						struct stat buf1 = text[i]->statistic;
						struct stat buf2 = text[j]->statistic;

						long int time1 = buf1.st_mtimespec.tv_sec;
						long int time2 = buf2.st_mtimespec.tv_sec;

						if (time1 < time2 || (time1 == time2 && mx_strcmp(text[i]->name, text[j]->name) > 0)) {
							swap(&text[i], &text[j]);
						}

						was_here = true;

					}

				}
			}
		}
	}

	if (!was_here) {
		
		for (int i = 0; text[i + 1] != NULL; i++) {
			for (int j = i + 1; text[j] != NULL; j++) {

				if (mx_strcmp(text[i]->name, text[j]->name) > 0) {
					swap(&text[i], &text[j]);
				}
			}
		}
	}

	if ((*flags)->r) {

		int len = 0;

		for (int i = 0; text[i] != NULL; i++) {
			len++;
		}

		for (int i = 0; i < len / 2; i++) {
			swap(&text[i], &text[len - i - 1]);
		}

	}

}



