#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"
#include "setup.h"

status_t split(const string str, char delimiter, size_t * str_num, string ** fields ){

	size_t i;
	char *aux, *q, *p;
	char delim[2];

	if (str == NULL || str_num == NULL)
		return ERROR_NULL_POINTER;

	if( (aux = strdupl(str)) == NULL)
	{	
		*str_num = 0;
		return ERROR_MEMORY;
	}

	for(i = 0, *str_num = 0; str[i]; i++)
	{
		if( str[i] == delimiter)
			(*str_num)++;
	}

	(*str_num)++;

	if((*fields = (string *)malloc((*str_num)* sizeof(string))) == NULL)
	{
		*str_num = 0;
		free(aux);
		return ERROR_MEMORY;
	}

	delim[0] = delimiter;
	delim[1] = '\0';

	for(i = 0, q = aux; (p = strtok (q, delim)) != NULL; q = NULL, i++)
	{
		if(( (*fields)[i] = strdupl(p)) == NULL)
		{
			free(aux);
			destroy_strings( fields, str_num);
			*str_num = 0;
			return ERROR_MEMORY;
		}

	}

	free(aux);

	return OK;

}

status_t read_line(char ** str, bool_t *eof, FILE * file_str){

	size_t alloc_size;
	char c;
	char *aux;
	size_t used_size;

	if (str == NULL || eof == NULL || file_str == NULL)
		return ERROR_NULL_POINTER;

	if((*str = (char *)malloc(INIT_SIZE * sizeof(char))) == NULL)
		return ERROR_MEMORY;

	alloc_size = INIT_SIZE;

	used_size = 0;
	while ((c = fgetc(file_str)) != '\n' && c != EOF)
	{
		if(used_size == alloc_size - 1)
		{
			if((aux = (char *)realloc(*str, (alloc_size + CHOP_SIZE) * sizeof(char))) == NULL)
			{
				free(str);
				return ERROR_MEMORY;
			}
			*str = aux;
			alloc_size += CHOP_SIZE;

		}

		(*str)[ used_size++ ] = c;
	}

	(*str)[ used_size ] = '\0';

	*eof = ( c == EOF )? TRUE : FALSE;

	return OK;

}

status_t destroy_strings(char *** strings, size_t *l ){

	size_t i;

	if ( strings == NULL || l == NULL)
		return ERROR_NULL_POINTER;

	for (i = 0; i < *l; i++)
	{	
		free((*strings)[i]);
		(*strings)[i] = NULL;
	}

	free ( *strings);

	*strings = NULL;
	*l = 0;

	return OK;

}

char * strdupl(const char *str){

	char * aux;
	size_t len, i;

	if (str == NULL)
		return NULL;

	len = strlen(str);

	if((aux = (char *) malloc( sizeof(char) * (len + 1))) == NULL)
		return NULL;

	for( i = 0; (aux[i] = str [i]); i++ );

	return aux;
}