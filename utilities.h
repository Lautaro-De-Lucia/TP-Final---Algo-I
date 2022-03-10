#ifndef UTILITIES__H
#define UTILITIES__H

#include <stdio.h>

#include "setup.h"

#define INIT_SIZE 10
#define CHOP_SIZE 10

status_t split(const string str, char delimiter, size_t * str_num, string ** fields );
status_t destroy_strings(char *** strings, size_t *l ); 	
char * strdupl(const char *str);
status_t read_line(char ** str, bool_t *eof, FILE * file_str);

#endif

