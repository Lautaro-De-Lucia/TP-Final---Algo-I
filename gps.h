#ifndef GPS__H
#define GPS__H

#include <stdio.h>
#include "setup.h"
#include "adtgps.h"
#include "adtvector.h"
#include "utilities.h"

#define NMEA_ID "$GPGGA"
#define MASK_SUM 0x7F
#define MINUTES_IN_DEGREES 60
#define	ALTITUDE_POSITION 9
#define PARSE_DELIMITER ','

status_t set_date_to_local_year_month_day( size_t * date );
bool_t validate_sum(char *str );
bool_t is_gpgga( char * str );
string remove_empty_fields_csv_line(const string str1, size_t * empty_fields, char delimiter);
status_t get_nmea_line ( FILE *file_gps , char delimiter , char ** nmea_line , bool_t * eof);
status_t parse_nmea_file ( FILE *file_gps , ADT_Vector_t * v);
status_t load_GPS_point( ADT_GPS_point_t *pt , string* str);
status_t Print_GPS_point_as_csv_line_date_lat_long_alt (ADT_GPS_point_t* pt , char delim , FILE* fo);
status_t Print_GPS_point_as_csv_line_long_lat_alt(ADT_GPS_point_t* pt , char delim , FILE* fo);
double convert_longitude_str ( char* longitude_str , char* cardinal); 
double convert_latitude_str ( char* latitude_str , char* cardinal);

#endif
