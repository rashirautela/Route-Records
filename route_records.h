#ifndef ROUTERECORDS_H
#define ROUTERECORDS_H
#include <stdio.h>

typedef struct RouteRecord 
{
    char originAirport[4];
    char destinAirport[4];
    char airlineCode[3];
    int passengerCnt[6];
} RouteRecord;
typedef enum SearchType 
{
    ROUTE,
    ORIGIN,
    DESTINATION,
    AIRLINE
} SearchType;
RouteRecord* createRecords( FILE* );
int fillRecords( RouteRecord*, FILE* );
int findAirlineRoute( RouteRecord*, int, const char*, const char*, const char*, int );
void searchRecords( RouteRecord*, int, const char*, const char*, SearchType );
void printMenu();

#endif