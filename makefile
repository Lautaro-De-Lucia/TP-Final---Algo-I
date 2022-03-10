CFLAGS = -ansi -pedantic -Wall
cc = gcc

all: gpsviewer

gpsviewer: main.o gps.o adtgps.o adtvector.o utilities.o errors.o 
		$(cc) $(CFLAGS) -o gpsviewer main.o adtgps.o adtvector.o errors.o utilities.o gps.o

main.o: main.c main.h gps.h adtgps.h adtvector.h setup.h errors.h
		$(cc) $(CFLAGS) -c main.c 

gps.o: gps.c gps.h setup.h adtgps.h adtvector.h utilities.h 
		$(cc) $(CFLAGS) -c gps.c

adtvector.o: adtvector.c adtvector.h setup.h utilities.h 
		$(cc) $(CFLAGS) -c adtvector.c			

adtgps.o: adtgps.c adtgps.h setup.h 
		$(cc) $(CFLAGS) -c adtgps.c	

utilities.o: utilities.c utilities.h setup.h 
		$(cc) $(CFLAGS) -c utilities.c					

errors.o: errors.c errors.h setup.h 
		$(cc) $(CFLAGS) -c errors.c			

				
