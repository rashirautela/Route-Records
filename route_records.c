#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route_records.h"

// creating records
RouteRecord* createRecords( FILE* fileIn ) 
{
    // initializing necessary variables
    char data[50];
    int i = 0;
    int j = 0;
    int count = 0;
    RouteRecord* currentRecords = NULL;
    // grab first line of records in data.csv
    fgets(data,50,fileIn);
    // count records
    while(fgets(data,50,fileIn) != NULL) 
    {
        count++;
    }
    // creating dynamically allocated array for RouteRecords
    currentRecords = (RouteRecord*)malloc(count * (sizeof(RouteRecord)));
    // initialize all passenger counts to 0 in the array
    for (i = 0; i < count; i++) 
    {
        for (j = 0; j < 6; j++) 
        {
            currentRecords[i].passengerCnt[j] = 0;
        }
    }
    // rewind file
    rewind(fileIn);
    // return dynamically allocated array
    return currentRecords;
}
int fillRecords( RouteRecord* r, FILE* fileIn ) 
{
    // initializing necessary variables
    char data[100];
    int month;
    int totalPassengers, count, fRoute = 0;
    char origAir[4];
    char desAir[4];
    char airline[3];
    char passengers[20];
    
    
    // grabs first line of file
    fgets(data,100,fileIn);
    // while loop to fill in the different input values into the record struct
    while(fgets(data,100,fileIn) != NULL) 
    {
        // parses data in our file
        sscanf(data, "%d,%[^,],%[^,],%[^,],%[^,],%d", &month,origAir,desAir,airline,passengers,&totalPassengers);
        fRoute = findAirlineRoute(r,strlen(data),origAir,desAir,airline,count);
        // if-else branch that checks if the route is already in the array
        // if it is not found it will create a location for it in the array
        // else, if it is found, it will place the total number of passengers into its proper month
        if (fRoute == -1) 
        {
            strcpy(r[count].originAirport, origAir);
            strcpy(r[count].destinAirport, desAir);
            strcpy(r[count].airlineCode, airline);
            r[count].passengerCnt[month - 1] = totalPassengers;
            count++;
        }
        else 
        {
            r[fRoute].passengerCnt[month - 1] = totalPassengers;
        }
    }
    // return number of actual route records
    // would it be -1 because we are always one ahead of the actual record count?
    return count;
}
// checks if the airline route is already in the RouteRecord struct using recursive function
int findAirlineRoute( RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx )
{
    if (curIdx < 0) 
    {
        return -1;
    }
    else if ((strcmp(r[curIdx].originAirport, origin) == 0) && (strcmp(r[curIdx].destinAirport, destination) == 0) && (strcmp(r[curIdx].airlineCode, airline) == 0)) 
    {
        return curIdx;
    }
    else 
    {
        return findAirlineRoute(r,length,origin,destination,airline,(curIdx - 1));
    }
}
// This function searches the RouteRecord array and prints out the results of the search
void searchRecords( RouteRecord* r, int length, const char* key1, const char* key2, SearchType st ) 
{
    int i, j, count, totalPassengers, P1, P2, P3, P4, P5, P6, avg = 0;
    
    // ROUTE
    if (st == 0) 
    {
        // traverses through the route records using the unique route record count
        for (i = 0; i < length; i++) 
        {
            // compares destination airport and the first key
            // if destination and key1 are the same, then it adds up passengers and prints out the route
            if ((strcmp(r[i].originAirport, key1) == 0) && (strcmp(r[i].destinAirport, key2) == 0)) 
            {
                printf("%s (%s-%s) ",r[i].airlineCode, r[i].originAirport, r[i].destinAirport);
                P1 += r[i].passengerCnt[0];
                P2 += r[i].passengerCnt[1];
                P3 += r[i].passengerCnt[2];
                P4 += r[i].passengerCnt[3];
                P5 += r[i].passengerCnt[4];
                P6 += r[i].passengerCnt[5];
                // adds up all the passengers
                for(j = 0; j < 6; j++) 
                {
                    totalPassengers += r[i].passengerCnt[j];
                }
                count++;
            }
        }
        avg = totalPassengers / 6;
        printf("\n%d matches were found.\n\n", count);
        printf("Statistics\nTotal Passengers:    %d\n", totalPassengers);
        printf("Total Passengers in Month 1:     %d\n", P1);
        printf("Total Passengers in Month 2:     %d\n", P2);
        printf("Total Passengers in Month 3:     %d\n", P3);
        printf("Total Passengers in Month 4:     %d\n", P4);
        printf("Total Passengers in Month 5:     %d\n", P5);
        printf("Total Passengers in Month 6:     %d\n\n", P6);
        printf("Average Passengers per Month:      %d\n", avg);
    }
    // ORIGIN
    else if (st == 1) 
    {
        // traverses through the route records using the unique route record count
        for (i = 0; i < length; i++) 
        {
            // compares origin airport and the first key
            // if origin and key1 are the same, then it adds up passengers and prints out the route
            if (strcmp(r[i].originAirport, key1) == 0) 
            {
                printf("%s (%s-%s) ",r[i].airlineCode, r[i].originAirport, r[i].destinAirport);
                P1 += r[i].passengerCnt[0];
                P2 += r[i].passengerCnt[1];
                P3 += r[i].passengerCnt[2];
                P4 += r[i].passengerCnt[3];
                P5 += r[i].passengerCnt[4];
                P6 += r[i].passengerCnt[5];
                // adds up all the passengers
                for(j = 0; j < 6; j++) {
                    totalPassengers += r[i].passengerCnt[j];
                }
                count++;
            }
        }
        avg = totalPassengers / 6;
        printf("\n%d matches were found.\n\n", count);
        printf("Statistics\nTotal Passengers:    %d\n", totalPassengers);
        printf("Total Passengers in Month 1:     %d\n", P1);
        printf("Total Passengers in Month 2:     %d\n", P2);
        printf("Total Passengers in Month 3:     %d\n", P3);
        printf("Total Passengers in Month 4:     %d\n", P4);
        printf("Total Passengers in Month 5:     %d\n", P5);
        printf("Total Passengers in Month 6:     %d\n\n", P6);
        printf("Average Passengers per Month:      %d\n", avg);
    }
    //DESTINATION
    else if (st == 2) 
    {
        // traverses through the route records using the unique route record count
        for (i = 0; i < length; i++) 
        {
            // compares destination airport and the first key
            // if destination and key1 are the same, then it adds up passengers and prints out the route
            if (strcmp(r[i].destinAirport, key1) == 0) 
            {
                printf("%s (%s-%s) ",r[i].airlineCode, r[i].originAirport, r[i].destinAirport);
                P1 += r[i].passengerCnt[0];
                P2 += r[i].passengerCnt[1];
                P3 += r[i].passengerCnt[2];
                P4 += r[i].passengerCnt[3];
                P5 += r[i].passengerCnt[4];
                P6 += r[i].passengerCnt[5];
                // adds up all the passengers
                for(j = 0; j < 6; j++) {
                    totalPassengers += r[i].passengerCnt[j];
                }
                count++;
            }
        }
        avg = totalPassengers / 6;
        printf("\n%d matches were found.\n\n", count);
        printf("Statistics\nTotal Passengers:    %d\n", totalPassengers);
        printf("Total Passengers in Month 1:     %d\n", P1);
        printf("Total Passengers in Month 2:     %d\n", P2);
        printf("Total Passengers in Month 3:     %d\n", P3);
        printf("Total Passengers in Month 4:     %d\n", P4);
        printf("Total Passengers in Month 5:     %d\n", P5);
        printf("Total Passengers in Month 6:     %d\n\n", P6);
        printf("Average Passengers per Month:      %d\n", avg);
    }
    // AIRLINE
    else if (st == 3) 
    {
        // traverses through the route records using the unique route record count
        for (i = 0; i < length; i++) 
        {
            // compares airline and the first key
            // if airline and key1 are the same, then it adds up passengers and prints out the route
            if (strcmp(r[i].airlineCode, key1) == 0) 
            {
                printf("%s (%s-%s) ",r[i].airlineCode, r[i].originAirport, r[i].destinAirport);
                P1 += r[i].passengerCnt[0];
                P2 += r[i].passengerCnt[1];
                P3 += r[i].passengerCnt[2];
                P4 += r[i].passengerCnt[3];
                P5 += r[i].passengerCnt[4];
                P6 += r[i].passengerCnt[5];
                // adds up all the passengers
                for(j = 0; j < 6; j++) 
                {
                    totalPassengers += r[i].passengerCnt[j];
                }
                count++;
            }
        }
        avg = totalPassengers / 6;
        printf("\n%d matches were found.\n\n", count);
        printf("Statistics\nTotal Passengers:    %d\n", totalPassengers);
        printf("Total Passengers in Month 1:     %d\n", P1);
        printf("Total Passengers in Month 2:     %d\n", P2);
        printf("Total Passengers in Month 3:     %d\n", P3);
        printf("Total Passengers in Month 4:     %d\n", P4);
        printf("Total Passengers in Month 5:     %d\n", P5);
        printf("Total Passengers in Month 6:     %d\n\n", P6);
        printf("Average Passengers per Month:      %d\n", avg);
    }
}
// This function prints the menu
void printMenu() 
{
    printf( "\n\n######### Airline Route Records Database MENU #########\n" );
    printf( "1. Search by Route\n" );
    printf( "2. Search by Origin Airport\n" );
    printf( "3. Search by Destination Airport\n" );
    printf( "4. Search by Airline\n" );
    printf( "5. Quit\n" );
    printf( "Enter your selection: " );
}