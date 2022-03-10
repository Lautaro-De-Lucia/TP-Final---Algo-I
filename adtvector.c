#include <stdio.h>
#include <stdlib.h>

#include "setup.h"
#include "adtvector.h"
#include "utilities.h"

status_t ADT_Vector_new (ADT_Vector_t **pv)
{
	if (pv == NULL)
		return ERROR_NULL_POINTER;

	if((*pv = (ADT_Vector_t*) malloc (sizeof(ADT_Vector_t))) == NULL)
	{
		(*pv)->elements = NULL;
	    (*pv)->size = 0;
	    return ERROR_MEMORY;	
    }

	(*pv)->size = 0;

	return OK;

}

size_t ADT_Vector_get_size (const ADT_Vector_t *v){
	return v->size;
}

void * ADT_Vector_get_element_at_pos( const ADT_Vector_t *v , size_t position ){
	return v->elements[position];
}

bool_t ADT_Vector_equals (const ADT_Vector_t *v1 , const ADT_Vector_t *v2 , bool_t (*pf)(void* , void*)) 
{    
    
    size_t i;

    if ( v1 == NULL || v2 == NULL)
        return FALSE;
    if ( v1->size != v2->size)
    	return FALSE;

    for (i = 0 ; i<v1->size;i++)
    	if(((*pf)(v1->elements[i],v2->elements[i]))!=0)
    		return FALSE;

    return TRUE;	
}

status_t ADT_Vector_delete (ADT_Vector_t ** pv , status_t (*pf) (void*)){

   	size_t i;
   	status_t st;

    if (pv == NULL || pf == NULL)
    	return ERROR_NULL_POINTER;

    for ( i = 0 ; i < (*pv)->size ; i++)
    	if((st = (*pf)((*pv)->elements[i]))!=OK)
    		return st;
    
    free((*pv)->elements);
    (*pv)->elements = NULL;

    free(*pv);
    *pv = NULL;

    return OK;
}

status_t ADT_Vector_clone ( ADT_Vector_t* v , ADT_Vector_t * pc , void * (*pf)(const void*) , status_t (*pf2)(void*) )
{    
    
	size_t i;
    size_t j;
    status_t st;
    ADT_Vector_t * aux;

    if (v == NULL || pc == NULL || pf == NULL)
    	return ERROR_NULL_POINTER;

    if((st = ADT_Vector_new(&pc)))
    	return st;

    for ( i = 0 ; i < v->size ; i++ )
    {
    	aux = (*pf)(v->elements[i]);
    	if (aux == NULL){
    		for( j = 0 ; j < pc-> size ; j++)
                (*pf2)(v->elements[j]);
    	v->elements = NULL;	
        }
    }

    return OK;
}   

status_t ADT_Vector_append ( ADT_Vector_t * v , void * elem ){

	void ** aux;

	if ( v == NULL || elem == NULL )
		return ERROR_NULL_POINTER;

	if (( aux = (void**) realloc( v-> elements, (v->size + 1) * sizeof (void*))) == NULL)
		return ERROR_MEMORY;

	v->elements = aux;
	v->elements [v->size] = elem;
	v->size++;

	return OK;

}

status_t ADT_Vector_print_on_terminal (ADT_Vector_t * v, status_t (*pf) (void *)){

	size_t i;

	for ( i = 0 ; i < v->size ; i++ ){
		(*pf)( v->elements[i]);
	}

	return OK;

}

status_t ADT_Vector_set_header_file(ADT_Vector_t *v , char * str){

	if( v == NULL || str == NULL)
		return ERROR_NULL_POINTER;

	v->header_file = str;

	return OK;
}

status_t ADT_Vector_set_footer_file(ADT_Vector_t *v , char * str){

	if( v == NULL || str == NULL)
		return ERROR_NULL_POINTER;

	v->footer_file = str;

	return OK;

}


status_t ADT_Vector_export(const ADT_Vector_t *v , FILE * fo, char delim , status_t (*pf)(void* , char , FILE*)){

	size_t i;
	status_t st;
	FILE *file_header;
	FILE *file_footer;
	char c;

	if ( v == NULL || fo == NULL || pf == NULL )
		return ERROR_NULL_POINTER;

	if (v->header_file != NULL)
		if((file_header = fopen(v->header_file,"rt")) == NULL)
			return ERROR_HEADER_FILE;

	if (v->footer_file != NULL)
		if((file_footer = fopen(v->footer_file,"rt")) == NULL)
			return ERROR_FOOTER_FILE;	

	if (v->header_file != NULL){
	while((c = fgetc(file_header)) != EOF)
		fputc(c,fo);	
	}

	for ( i = 0 ; i < v->size ; i++ ){
		if ((st = (*pf)(v->elements[i],delim, fo )) != OK)
			return st;
	}

	if(v->footer_file != NULL){
	while((c = fgetc(file_footer)) != EOF)
		fputc(c,fo);	
	}

	return OK;

}


status_t ADT_Vector_sort ( ADT_Vector_t * v , bool_t (*compare) (void*,void*) , void (*swap) (void*,void*)){

	size_t i,j,min;
	size_t size = v->size;

		for ( i = 0 ; i < size - 1 ; i++ ){
			min = i;
			for ( j = i + 1 ; j < size ; j++ ){
				if((*compare)(v->elements[j],v->elements[min]))
					min = j;
			}
			(*swap)(v->elements[min],v->elements[i]);
		}

	return OK;	
}	