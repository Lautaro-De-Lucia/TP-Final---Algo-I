#ifndef ADTVECTOR__H
#define ADTVECTOR__H

#include <stdio.h>

#include "setup.h"
#include "utilities.h"

typedef struct {
	void ** elements;
	size_t size;
	string header_file;
	string footer_file;
} ADT_Vector_t; 

status_t ADT_Vector_new (ADT_Vector_t **pv);
size_t ADT_Vector_get_size (const ADT_Vector_t *v);
void * ADT_Vector_get_element_at_pos( const ADT_Vector_t *v , size_t position );
status_t ADT_Vector_delete (ADT_Vector_t ** pv , status_t (*pf) (void*));
status_t ADT_Vector_export(const ADT_Vector_t *v , FILE * fo, char delim , status_t (*pf)(void* , char , FILE*));
status_t ADT_Vector_clone (ADT_Vector_t* v , ADT_Vector_t * pc , void * (*pf)(const void*) , status_t (*pf2)(void*));
bool_t ADT_Vector_equals (const ADT_Vector_t *v1 , const ADT_Vector_t *v2 , bool_t (*pf)(void* , void*)); 
status_t ADT_Vector_append( ADT_Vector_t * v , void * elem );
status_t ADT_Vector_print_on_terminal (ADT_Vector_t * v , status_t (*pf) (void *));
status_t ADT_Vector_set_header_file(ADT_Vector_t *v , char * str);
status_t ADT_Vector_set_footer_file(ADT_Vector_t *v , char * str);
status_t ADT_Vector_sort( ADT_Vector_t * v , bool_t (*compare) (void*,void*) , void (*swap) (void*,void*));


#endif