#include "utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *mystrndup(const char *str, size_t n) {
    size_t len = strnlen(str, n);
    char *copy = malloc(len + 1);

    if (copy) {
        memcpy(copy, str, len);
        copy[len] = '\0';
    }
    return copy;
}