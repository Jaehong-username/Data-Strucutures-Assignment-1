/******************************************************************************************************************
* Programmer: Jaehong Lee
* Class: CptS 122, Fall 2023; Lab Section 3 (Tuesday 1:20PM - 4:20PM)
* Programming Assignment: PA1
* Date: September 8, 2023
* Description: This PA assignment does data analysis on the FitbitData csv file. On this csv
* file, there are some missing data at a certain column and a row with some duplicates of data.
* Data entries that are duplicated multiple times are deduped. Then missing values are inserted with
* invalid data values (-1.00 and 999 were used to represent invalid data to not skew the data results
* in terms of total amount, max, average etc.
* The filtered, deduped and cleansed data is uploaded on the output Results.csv file ater implenting this program.
******************************************************************************************************************/


#include "function.h"

/********************************************************************************************************************
* Function: printData()                  
* Date Created: 8/30/2023                                       
* Date Last Modified: 9/1/2023                                       
* Description: This function prints out all the fields of struct in the array of structs      
* Input parameters: fitbitdata_array: the array of struct of fitbit data which has been filtered, cleansed, deduped
*                   for printing them out on the console.
*                   size: the number of elements in the array.
* Returns: Nothing
* Preconditions: FitbitData.csv File must be opened successfully to read the data before implementing the function.                                      *
*********************************************************************************************************************/


void printData(FitbitData fitbitdata_array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("\nPatient[%d] name: %s", i, fitbitdata_array[i].patient);
		printf("\nPatient[%d] minute: %s", i, fitbitdata_array[i].minute);
		printf("\nPatient[%d] calories: %lf", i, fitbitdata_array[i].calories);
		printf("\nPatient[%d] distance: %lf", i, fitbitdata_array[i].distance);
		printf("\nPatient[%d] floors: %u", i, fitbitdata_array[i].floors);
		printf("\nPatient[%d] heartrate: %u", i, fitbitdata_array[i].heartRate);
		printf("\nPatient[%d] steps: %u", i, fitbitdata_array[i].steps);
		printf("\nPatient[%d] sleep level: %d", i, fitbitdata_array[i].sleepLevel);
		printf("\n\n");
	}


}