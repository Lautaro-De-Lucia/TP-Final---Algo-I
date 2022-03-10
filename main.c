#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "gps.h"
#include "adtvector.h"
#include "adtgps.h"
#include "setup.h"
#include "errors.h"

status_t validate_arguments(int argc, char const *argv[], config_t * config);

int main(int argc, char const *argv[]){

	FILE *file_gps;
	FILE *file_output;
	status_t st;
	ADT_Vector_t * v;
	config_t config;

	if((st = validate_arguments(argc,argv,&config)) != OK){
		print_error(st);
		return st;
	}

	if((file_gps = fopen(config.input_file,"rt")) == NULL){
		print_error(ERROR_INPUT_FILE);
		return ERROR_INPUT_FILE;
	}

	if((file_output = fopen(config.output_file,"wt")) == NULL){
		print_error(ERROR_OUTPUT_FILE);
		return ERROR_OUTPUT_FILE;
	}

	if ((st = ADT_Vector_new (&v)) != OK){
		print_error(st);
		return st;
	}

	if ((st = parse_nmea_file(file_gps, v )) != OK){
		print_error(st);
		return st;
	}

	fclose(file_gps);

	if (( st = ADT_Vector_sort( v , ADT_GPS_point_compare_by_date, ADT_GPS_point_swap)) != OK){
		print_error(st);
		return st;
	}

	switch (config.format){

		case OUTPUT_FORMAT_CSV:
		if (( st = ADT_Vector_export( v , file_output , CSV_DELIMITER , Print_GPS_point_as_csv_line_date_lat_long_alt )) != OK){
			print_error(st);
			return st;
		}
		break;

		case OUTPUT_FORMAT_KML:
		if (( st = ADT_Vector_set_header_file( v , HEADER_FILE )) != OK){
			print_error(st);
			return st;
		}
		if (( st = ADT_Vector_set_footer_file( v , FOOTER_FILE )) != OK){
			print_error(st);
			return st;
		}
		if (( st = ADT_Vector_export( v , file_output , KML_DELIMITER , Print_GPS_point_as_csv_line_long_lat_alt )) != OK){
			print_error(st);
			return st;
		}
		break;

	}

	fclose(file_output);

	return OK;

}

status_t validate_arguments(int argc, char const *argv[], config_t * config)
{
	if(argv == NULL || config == NULL)
		return ERROR_NULL_POINTER;

	if(argc != MAX_CMD_ARGS)
		return ERROR_PROGRAM_INVOCATION;

	if(strcmp(argv[CMD_ARG_FLAG_FMT],"-fmt"))
		return ERROR_PROGRAM_INVOCATION;

	if(strcmp(argv[CMD_ARG_FLAG_OUT],"-out"))
		return ERROR_PROGRAM_INVOCATION;

	if(!strcmp(argv[CMD_ARG_FORMAT],FMT_CSV))
		config->format = OUTPUT_FORMAT_CSV;
	else if(!strcmp(argv[CMD_ARG_FORMAT],FMT_KML))
		config->format = OUTPUT_FORMAT_KML;
	else
		return ERROR_INVALID_FORMAT;

	config->input_file = strdupl(argv[CMD_ARG_INPUT]);
	config->output_file = strdupl(argv[CMD_ARG_OUTPUT]);

	return OK;
}

