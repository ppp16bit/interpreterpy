#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>

/* when i call strndup i get an error maybe its bc im using windows
i like to play games dont judge me :p

i was recommended to set it manually*/
char *mystrndup(const char *str, size_t n);

#endif