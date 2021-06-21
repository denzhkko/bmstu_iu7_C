#ifndef __MYSTDIO_H__
#define __MYSTDIO_H__

#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>

#include "macrologger.h"

#include "num.h"

#define INCORRECT_FORMAT                -1

int my_snprintf(char *s, size_t n, const char *format, ...);

#endif // __MYSTDIO_H__
