#ifndef SETUP__H
#define SETUP__H

typedef char* string;

typedef enum{
	OUTPUT_FORMAT_CSV,
	OUTPUT_FORMAT_KML
} output_format_t;

typedef struct{
	output_format_t format;
	char* input_file;
	char* output_file;
} config_t;

typedef enum {TRUE,FALSE} bool_t;

typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
	ERROR_INPUT_FILE,
	ERROR_OUTPUT_FILE,
	ERROR_INVALID_DATE,
	ERROR_INVALID_LONGITUDE,
	ERROR_INVALID_LATITUDE,
	ERROR_INVALID_ALTITUDE,
	ERROR_HEADER_FILE,
	ERROR_FOOTER_FILE,
	ERROR_INVALID_FORMAT,
	ERROR_PROGRAM_INVOCATION,
	ERROR_TIME
} status_t;

#endif