#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "gps.h"
#include "setup.h"
#include "adtgps.h"
#include "adtvector.h"
#include "utilities.h"

status_t set_date_to_local_year_month_day ( size_t * date ){

	time_t local_time;
	struct tm * Time_struct; 
	size_t year;
	size_t month;
	size_t day;

	time (&local_time);

	Time_struct = localtime(&local_time);

	year = (Time_struct->tm_year+1900) * 10000000000;
	month = (Time_struct->tm_mon + 1) * 100000000;
	day = (Time_struct->tm_mday) * 1000000;

	*date = year + month + day + *date;

	return 0;

}

bool_t validate_sum(char * s){

	/*Precondicion: Puntero no nulo*/

	int sum = 0;
	int result = 0;
	char verify[2];
	char * aux;
	char * temp;

	aux = s;

	aux++;

	while(*aux != '*')
	{
		sum ^= (*aux);
		aux++;
	}

	sum &= MASK_SUM;
    
	aux++;

	verify[0] = *aux;
	aux++;
	verify[1] = *aux;
	verify[2] = '\0';
   
	result = strtoul(verify,&temp,16);

	if(sum != result)
		return FALSE;

	return TRUE;

}

bool_t is_gpgga( char * str ){

	/*Precondicion : Puntero no nulo*/

	char aux[6];

	memcpy(aux,str,6);

	aux[6] = '\0';

	if(!strcmp(aux,NMEA_ID))
		return TRUE;
	return FALSE;

}

string remove_empty_fields_csv_line(const string str , size_t * empty_fields , char delimiter){

	/*Precondición: Puntero no nulo*/

	size_t i,j;
	size_t len;
	string aux;

	len = strlen(str);

	if((aux = (char *) malloc( sizeof(char) * (len + 1))) == NULL)
		return NULL;

	for ( i = 0 , j = 0 ; i < len ; i++ , j++ ){

		if(str[j] == delimiter && str[j+1] == delimiter)
			j++;

		aux[i] = str[j];

	}

	*empty_fields = j - i;

	return aux;

}

status_t get_nmea_line ( FILE *file_gps , char delimiter , char ** nmea_line, bool_t * eof) {

	status_t st;
	string aux;
	int dummy = 1;
	size_t empty_fields;

	if( file_gps == NULL || nmea_line == NULL || eof == NULL)
		return ERROR_NULL_POINTER;

	while (dummy){

		if ((st = (read_line(&aux,eof,file_gps))) != OK ){
			return st;
		}

		if(*eof == TRUE)
			break;

		if ((is_gpgga(aux)) != TRUE)
			continue;

		if ((validate_sum(aux)) != TRUE)
			continue;

		if (((*nmea_line) = remove_empty_fields_csv_line(aux,&empty_fields,delimiter)) == NULL)
			return ERROR_MEMORY;

		if(empty_fields > 1)
			continue;

		return OK;
	
	}

	return OK;

}

status_t parse_nmea_file ( FILE *file_gps , ADT_Vector_t * v ){

	status_t st;
	bool_t eof;
	string nmea_line;
	char delimiter = PARSE_DELIMITER;
	ADT_GPS_point_t pt;
	ADT_GPS_point_t * new_point;
	size_t date;

	if (( st = ADT_GPS_point_new(&pt)) != OK)
		return st;

	if ((st = get_nmea_line (file_gps, delimiter , &nmea_line , &eof)) != OK){
		return st;
	}

	while (eof != TRUE){

		if (( new_point = ADT_GPS_clone_point( &pt )) == NULL){
			ADT_Vector_delete(&v,ADT_GPS_point_delete);
			return ERROR_MEMORY;
		}

		if (( st = ADT_GPS_point_from_nmea_line( new_point , nmea_line )) != OK){
			ADT_Vector_delete(&v,ADT_GPS_point_delete);
			return st;
		}

		date = ADT_GPS_point_get_date(new_point);

		if ((st = set_date_to_local_year_month_day(&date)) != OK)
			return st;

		ADT_GPS_point_set_date(new_point, date);


		if (( st = ADT_Vector_append( v , new_point )) != OK){
			ADT_Vector_delete(&v,ADT_GPS_point_delete);
			return st;
		}

		if ((st = get_nmea_line (file_gps, delimiter, &nmea_line , &eof)) != OK){
			ADT_Vector_delete(&v,ADT_GPS_point_delete);
			return st;
		}

	}

	return OK;

}

status_t load_GPS_point( ADT_GPS_point_t *pt , string* str){

	size_t aux1;
	double aux2;
	char *temp;

	if ( pt == NULL || str == NULL)
		return ERROR_NULL_POINTER;

	aux1 = (size_t) strtod(str[1],&temp);
			if(*temp && *temp != '\n')
				return ERROR_INVALID_DATE;
	ADT_GPS_point_set_date( pt , aux1 );
	aux2 = convert_latitude_str(str[2],str[3]);
	ADT_GPS_point_set_latitude( pt , aux2 );
	aux2 = convert_longitude_str(str[4],str[5]);
	ADT_GPS_point_set_longitude( pt , aux2 );
	aux2 = strtod(str[ALTITUDE_POSITION],&temp);
			if(*temp && *temp != '\n')
				return ERROR_INVALID_ALTITUDE;	
	ADT_GPS_point_set_altitude( pt , aux2 );

	return OK;

}

status_t Print_GPS_point_as_csv_line_date_lat_long_alt (ADT_GPS_point_t* pt , char delim , FILE* fo){

	if(pt == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	fprintf(fo,"%lu%c%f%c%f%c%f\n",
		ADT_GPS_point_get_date(pt),delim,
		ADT_GPS_point_get_latitude(pt),delim,
		ADT_GPS_point_get_longitude(pt),delim,
		ADT_GPS_point_get_altitude(pt));
			
	return OK;

}

status_t Print_GPS_point_as_csv_line_long_lat_alt(ADT_GPS_point_t* pt , char delim , FILE* fo){

	if(pt == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	fprintf(fo,"%f%c%f%c%f\n",
		ADT_GPS_point_get_longitude(pt),delim,
		ADT_GPS_point_get_latitude(pt),delim,
		ADT_GPS_point_get_altitude(pt));
			
	return OK;

}

double convert_longitude_str ( char* longitude_str , char* cardinal){

	char deg_str[3];
	char min_str[9];
	double deg;
	double min;	
	double total;
	char* temp;

	memcpy(deg_str,longitude_str,3);
	deg_str[3] = '\0';

	memcpy(min_str,&longitude_str[3],9);
	min_str[9] = '\0';

	deg = strtod(deg_str,&temp);

	min = strtod(min_str,&temp);

	if(!strcmp(cardinal,"W"))
		total = -(deg+min/MINUTES_IN_DEGREES);
	else
		total = deg +min/MINUTES_IN_DEGREES;

	return total;
}

double convert_latitude_str ( char* longitude_str , char* cardinal){

	char deg_str[2];
	char min_str[8];
	double deg;
	double min;	
	double total;
	char* temp;

	memcpy(deg_str,longitude_str,2);
	deg_str[2] = '\0';

	memcpy(min_str,&longitude_str[2],8);
	min_str[8] = '\0';

	deg = strtod(deg_str,&temp);

	min = strtod(min_str,&temp);

	if(!strcmp(cardinal,"S"))
		total = -(deg+min/MINUTES_IN_DEGREES);
	else
		total = deg +min/MINUTES_IN_DEGREES;

	return total;
}




