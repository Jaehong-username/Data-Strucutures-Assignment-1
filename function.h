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


#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <string.h>

#include <stdbool.h>

#include <stdlib.h>

typedef enum sleep
{
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3 //just treating it as an integer if I say NONE program perceives it as 0
} Sleep;

typedef struct fitbit
{
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel; //data type Sleep equals just like int with enum treating it as an int. enum enumerate!
} FitbitData;

void printData(FitbitData fitbitdata_array[], int size);



#endif