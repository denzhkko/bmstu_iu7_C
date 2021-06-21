#ifndef _FUNCS_H_
#define _FUNCS_H_

#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <inttypes.h>
#include <time.h>
#include <stdlib.h>

#define OKAY 0
#define INCORRECT_START -1
#define INCORRECT_COMMAND -2
#define FILE_CANNOT_BE_OPENED -3
#define FCLOSE_FAILED -4
#define FWRITE_FAILED -5
#define FSEEK_FAILED -6
#define FTELL_FAILED -7
#define FREAD_FAILED -8
#define EMPTY_FILE -9
#define INCORRECT_FILE_SIZE -10
#define UNKNOWN_EXIT_CODE -127

#define INCORRECT_START_MESS "Enter: ./main.exe <command> <filename>\n"
#define INCORRECT_COMMAND_MESS "Available commands: c for create, "\
"p for print, s for sort\n"
#define FSEEK_FAILED_MESS "fseek failed\n"
#define FTELL_FAILED_MESS "ftell failed\n"
#define FREAD_FAILED_MESS "fread failed\n"
#define EMPTY_FILE_MESS "Empty file\n"
#define INCORRECT_FILE_SIZE_MESS "Incorrect file size\n"
#define UNKNOWN_EXIT_CODE_MESS "Unknown error\n"

#define INCORRECT_START_ERROR 1
#define INCORRECT_COMMAND_ERROR 2
#define FILE_CANNOT_BE_OPENED_ERROR 3
#define FCLOSE_FAILED_ERROR 4
#define FWRITE_FAILED_ERROR 5
#define FSEEK_FAILED_ERROR 6
#define FTELL_FAILED_ERROR 7
#define FREAD_FAILED_ERROR 8
#define EMPTY_FILE_ERROR 9
#define INCORRECT_FILE_SIZE_ERROR 10
#define UNKNOWN_EXIT_CODE_ERROR 127

int fill_file(FILE *f, const size_t num_count);

int get_file_size(FILE *f, size_t *const size);

int print_file(FILE *f);

int sort_file(FILE *f);

int process_exit_code(const int exit_code);

#endif /* _FUNCS_H_ */
