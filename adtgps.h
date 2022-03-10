#ifndef ADTGPS__H
#define ADTGPS__H

#include <stdio.h>
#include <stdlib.h>

#include "setup.h"

typedef struct {
	size_t date;
	double latitude;
	double longitude;
	double altitude;
} ADT_GPS_point_t;

status_t ADT_GPS_point_new(ADT_GPS_point_t * p);
status_t ADT_GPS_point_delete(ADT_GPS_point_t * p);
status_t ADT_GPS_point_set_date(ADT_GPS_point_t * p, size_t d);
status_t ADT_GPS_point_set_latitude(ADT_GPS_point_t * p, double l);
status_t ADT_GPS_point_set_longitude(ADT_GPS_point_t * p, double l);
status_t ADT_GPS_point_set_altitude(ADT_GPS_point_t * p, double a);
status_t ADT_GPS_copy_point(ADT_GPS_point_t * p1 , const ADT_GPS_point_t * p2);
void ADT_GPS_point_swap( ADT_GPS_point_t * p1 , ADT_GPS_point_t * p2 );
bool_t ADT_GPS_point_compare_by_date ( ADT_GPS_point_t * p1 , ADT_GPS_point_t * p2 );
size_t ADT_GPS_point_get_date(ADT_GPS_point_t * p);
double ADT_GPS_point_get_latitude(ADT_GPS_point_t * p);
double ADT_GPS_point_get_longitude(ADT_GPS_point_t * p);
double ADT_GPS_point_get_altitude(ADT_GPS_point_t * p);
status_t ADT_GPS_sort_by_date( ADT_GPS_point_t * arr[] , size_t * size );
status_t ADT_GPS_point_print(ADT_GPS_point_t * p);
ADT_GPS_point_t * ADT_GPS_clone_point(const ADT_GPS_point_t * p);
status_t ADT_GPS_point_from_nmea_line ( ADT_GPS_point_t * p , char * str );

#endif
