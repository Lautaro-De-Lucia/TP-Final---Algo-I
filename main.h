#ifndef MAIN__H
#define MAIN__H

#include <stdio.h>

#include "setup.h"
#include "adtvector.h"
#include "adtgps.h"

#define FMT_CSV "csv"
#define FMT_KML "kml"

#define CSV_DELIMITER '|'
#define KML_DELIMITER ','
#define HEADER_FILE "kml_header.txt"
#define FOOTER_FILE "kml_footer.txt"

#define MAX_CMD_ARGS 6

#define CMD_ARG_FLAG_FMT 1
#define CMD_ARG_FORMAT 2
#define CMD_ARG_FLAG_OUT 3
#define CMD_ARG_OUTPUT 4
#define CMD_ARG_INPUT 5

status_t validate_arguments(int argc, char const *argv[], config_t * config);

#endif