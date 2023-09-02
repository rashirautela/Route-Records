#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route_records.h"

int main(int argc, char* argv[])
{
    /* 1. Declare variables here */
    FILE* fileIn = NULL;
    char* fileName = argv[1];
    RouteRecord* records = NULL;
    int RouteCnt = 0;
    int userValue = 0;
    char key1[4];
    char key2[4];
    SearchType searchType;
    /* 2. Check command line arguments here. If a command line argument (for the file name) is missing,
    print out the following: ERROR: Missing file name and end the program */
    if (argc != 2) 
    {
        printf("ERROR: Missing file name\n");
        return 1;
    }
    /* 3. Attempt to open the file. Print out Opening <filename>... before you call fopen(). */
    printf("\nOpening %s...\n", fileName);
    fileIn = fopen(fileName, "r");
    /* 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program. */
    if (fileIn == NULL) 
    {
        printf("ERROR: Could not open file\n");
        return 1;
    }
    // 5. Do the following to load the records into an array of RouteRecords
    	
    /*5.1 Call createRecords(), which will read through the file once to find the total number of lines/records in the file.
    	Use this count, to dynamically allocate memory for an array of RouteRecords. It returns a pointer to that array.
    	Don't forget to rewind the file pointer.
    */
    records = createRecords(fileIn);
    		
    		
    /*5.2 Call fillRecords() to go through the CSV file again to fill in the values.
    	It will then return the actual number of items the array has.
    	Recall that not all records in the original CSV file will be entered into the array.
    	Print the number of unique routes operated by different airlines: Unique routes operated by airlines: ???
    */
    RouteCnt = fillRecords(records,fileIn);
    printf("Unique routes operated by airlines: %d\n", RouteCnt);
    		
    		
    //5.3 Close the the file.
    fclose(fileIn);
    // 6. Create an infinite loop that will do the following:
    while (1) 
    {
        //6.1 Call printMenu()
        printMenu();
    		
    	// 6.2 Ask the user to input a value for the menu
    	scanf("%d", &userValue);
    	
    	//6.3 Handle the case in which a non-integer value is entered
    	if (!((userValue >= 1) && (userValue <= 5))) 
        {
    	   
    	    printf("Invalid choice.");
    	    continue;
    	   
    	}
    	
    	//6.4 Create a switch/case statement to handle all the menu options
    	//6.4.1 Each option requires the user to enter a search key
	    //6.4.2 Quit needs to free the array
      // Goes through switch case
      // 1 - Search by route
      // 2 - Search by origin
      // 3 - Search by destination
      // 4 - Search by airline code
      // 5 - Exit program
    	switch (userValue) 
        {
    	   case 1:
    	   
    	    searchType = ROUTE;
    	    printf("Enter origin: ");
    	    scanf("%s", key1);
    	   
    	    printf("Enter destination: ");
    	    scanf("%s", key2);
    	   
    	    printf("\nSearching by route...\n");
    	    searchRecords( records, RouteCnt, key1, key2, searchType );
    	   
    	    break;
    	   
    	   case 2:
    	  
       	    searchType = ORIGIN;
    	    printf("Enter origin: ");
    	    scanf("%s", key1);
    	    printf("\nSearching by origin...\n");
    	    searchRecords( records, RouteCnt, key1, key2, searchType );
            break;
    	   case 3:
    	  
    	    searchType = DESTINATION;
    	    printf("Enter destination: ");
    	    scanf("%s", key1);
            printf("\nSearching by destination...\n");
    	    searchRecords( records, RouteCnt, key1, key2, searchType );
            break;
    	   case 4:
    	   
    	    searchType = AIRLINE;
    	    printf("Enter airline: ");
    	    scanf("%s", key1);
    	  
    	    printf("\nSearching by airline...\n");
    	    searchRecords( records, RouteCnt, key1, key2, searchType );
            break;
    	   case 5:
    	  
    	    printf("Good-bye!\n");
    	  
    	    return 0;
    	
    	   
    	}
    }
    return 0;
}