#include <stdio.h>
#include <stdlib.h>

#include "adtgps.h"
#include "utilities.h"
#include "gps.h"

status_t ADT_GPS_point_new(ADT_GPS_point_t * p)
{
	if(p == NULL)
		return ERROR_NULL_POINTER;

	if((p = (ADT_GPS_point_t *)malloc(sizeof(ADT_GPS_point_t))) == NULL)
		return ERROR_MEMORY;

	p->date = 0.0;
	p->latitude = 0.0;
	p->longitude = 0.0;
	p->altitude = 0.0;

	return OK;
}

status_t ADT_GPS_point_delete(ADT_GPS_point_t * p)
{
	if(p == NULL)
		return ERROR_NULL_POINTER;

	free(p);

	p = NULL;

	return OK;
}

void ADT_GPS_point_swap( ADT_GPS_point_t * p1 , ADT_GPS_point_t * p2 ){

	ADT_GPS_point_t * aux;
	aux = ADT_GPS_clone_point( p1 );
	ADT_GPS_copy_point( p1 , p2 );
	ADT_GPS_copy_point( p2 , aux);

}

status_t ADT_GPS_point_set_date(ADT_GPS_point_t * p, size_t d)
{
	/*Precondición: Puntero no nulo*/

	p->date = d;

	return OK;
}


status_t ADT_GPS_point_set_latitude(ADT_GPS_point_t * p, double l)
{
	/*Precondición: Puntero no nulo*/

	p->latitude = l;

	return OK;
}

status_t ADT_GPS_point_set_longitude(ADT_GPS_point_t * p, double l)
{
	/*Precondición: Puntero no nulo*/

	p->longitude = l;

	return OK;
}

status_t ADT_GPS_point_set_altitude(ADT_GPS_point_t * p, double a)
{
	/*Precondición: Puntero no nulo*/

	p->altitude = a;

	return OK;
}

status_t ADT_GPS_point_print(ADT_GPS_point_t * p)
{
	if(p == NULL)
		return ERROR_NULL_POINTER;

	printf("%lu\n",p->date);
	printf("%f\n",p->latitude);
	printf("%f\n",p->longitude);
	printf("%f\n",p->altitude);

	return OK;
}

ADT_GPS_point_t * ADT_GPS_clone_point(const ADT_GPS_point_t * p)
{

	/*Precondición: Puntero no nulo*/

	ADT_GPS_point_t * c;

	if((c = (ADT_GPS_point_t *)malloc(sizeof(ADT_GPS_point_t))) == NULL)
		return NULL;

	c->date = p->date;
	c->latitude = p->latitude;
	c->longitude = p->longitude;
	c->altitude = p->altitude;

	return c;
}

size_t ADT_GPS_point_get_date(ADT_GPS_point_t * p)
{
	return p->date;
}

double ADT_GPS_point_get_latitude(ADT_GPS_point_t * p)
{
	return p->latitude;
}
double ADT_GPS_point_get_longitude(ADT_GPS_point_t * p)
{
	return p->longitude;
}
double ADT_GPS_point_get_altitude(ADT_GPS_point_t * p)
{
	return p->altitude;
}

status_t ADT_GPS_copy_point(ADT_GPS_point_t * p1 , const ADT_GPS_point_t * p2){

	if ( p1 == NULL || p2 == NULL )
		return ERROR_NULL_POINTER;

	p1->date = p2->date;
	p1->latitude = p2->latitude;
	p1->longitude = p2->longitude;
	p1->altitude = p2->altitude;

	return OK;

}

status_t ADT_GPS_point_from_nmea_line ( ADT_GPS_point_t * p , char * nmea_line ){

	size_t str_num;
	char **fields;
	status_t st;

	if ((st = split(nmea_line,',',&str_num,&fields)) != OK)
		return st;

	if (( st = load_GPS_point(p,fields)) != OK)
		return st;

	return OK;

}

bool_t ADT_GPS_point_compare_by_date ( ADT_GPS_point_t * p1 , ADT_GPS_point_t * p2 ){

	/*Precondición: Puntero no nulo*/

	if (p1->date > p2->date)
		return TRUE;
	else
		return FALSE;

}