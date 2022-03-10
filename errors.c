#include <stdio.h>
#include "errors.h"
#include "setup.h"

char * error_dictionary[MAX_ERRORS] = {
	"Ok",
	"Error: Puntero nulo",
	"Error: Memoria insuficiente",
	"Error: Archivo de entrada",
	"Error: Archivo de salida",
	"Error(parseo): Valor de fecha inválido",
	"Error(parseo): Valor de longitud inválido",
	"Error(parseo): Valor de latitud inválido",
	"Error(parseo): Valor de altitud inválido",
	"Error: Archivo de encabezado",
	"Error: Archivo de pie de página",
	"Error: Formato inválido",
	"Error: Invocación del programa",
	"Error: Tiempo"
};

status_t print_error (status_t error){
	fprintf(stderr, "%s\n", error_dictionary[error]);
	return OK;
} 

