#ifndef __NONSTDIO_H__
#define __NONSTDIO_H__

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "rc.h"
#include "macrologger.h"

int skip_sep_symbols(FILE *source);

bool next_char_minus(FILE *const f);

int read_unsigned(FILE *const f, unsigned *const num);

#endif // __NONSTDIO_H__
