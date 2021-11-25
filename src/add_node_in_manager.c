#include "../inc/uls.h"

t_manager *add_node(char *data) {
    t_manager *new = (t_manager *)malloc(sizeof(t_manager));

    new->path = mx_strdup(data);
    new->name = mx_strdup(data);
    new->error = NULL;

    if (lstat(data, &(new->statistic)) == -1) {
        new->error = mx_strdup(strerror(errno));
    }

    new->open = NULL;

    return new;
}

t_manager *add_file_node(t_manager *node) {
    t_manager *new = (t_manager *)malloc(sizeof (t_manager));

    new->name = mx_strdup(node->name);
    new->path = mx_strdup(node->path);
    new->error = NULL;

    if (node->error != NULL) {
        new->error = mx_strdup(node->error);
    }

    if (node->open != NULL) {
        new->open = node->open;
    }
    else {
        new->open = NULL;
    }

    lstat(new->path, &(new->statistic));

    return new;
}

t_manager *add_named_node(char *name, char *path) {
    t_manager *new = (t_manager *) malloc(sizeof(t_manager));

    new->name = mx_strdup(name);

    new->path = mx_strdup(path);
    new->path = mx_strjoin(new->path, "/");
    new->path = mx_strjoin(new->path, name);

    new->error = NULL;

    if (lstat(new->path, &(new->statistic)) == -1) {
        new->error = mx_strdup(strerror(errno));
    }

    new->open = NULL;

    return new;
}

