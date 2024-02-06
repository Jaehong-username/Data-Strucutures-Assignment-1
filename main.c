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

int main(void)
{
	//FILE* Patient_File1;
	//Patient_File1 = fopen("Simplified data.csv", "r");

	FILE* Patient_File;
	//Patient_File= fopen("C:\\Users\\14253\\Downloads\\FitbitData.csv", "r");
	Patient_File = fopen("FitbitData.csv", "r"); //why this one is not working?? resolved!!!


	char line[100] = "";
	char result_line[8][100] = {"",""};
	FitbitData fitbitdata_array[1440] = { {"", "", 0.0, 0.0, 0, 0, 0, 0}, {"", "", 0.0, 0.0, 0, 0, 0, 0} };
	int lineNum = 0;

	//char tempString[100] = "";
	


	if (Patient_File != NULL) //opened successfully
	{
		fgets(line, 100, Patient_File);  //read in header line
		fputs(line, stdout); //stdout means to console
		
		fgets(line, 100, Patient_File);  //read in header line
		fputs(line, stdout); //stdout means to console

		//data cleaning/////////////////

		//while (fgets(line, 100, Patient_File) != NULL)      //if every time strtok used even if its for if checking
		//{
		//
		//	if (strtok(line, ",") == NULL) strcpy(fitbitdata_array[lineNum].patient, "missing");
		//	if (strtok(NULL, ",") == NULL) strcpy(fitbitdata_array[lineNum].minute, "missing");
		//	if (strtok(NULL, ",") == NULL) fitbitdata_array[lineNum].calories = -1.00;
		//	if (strtok(NULL, ",") == NULL) fitbitdata_array[lineNum].distance = -1.00;
		//	if (strtok(NULL, ",") == NULL) fitbitdata_array[lineNum].floors = 999;
		//	if (strtok(NULL, ",") == NULL) fitbitdata_array[lineNum].heartRate = 999;
		//	if (strtok(NULL, ",") == NULL) fitbitdata_array[lineNum].steps = 999;
		//	if (strtok(NULL, "\n") == NULL) fitbitdata_array[lineNum].sleepLevel = 999;

		//	lineNum++;

		//}

		/////////////////////////

		while (fgets(line, 100, Patient_File) != NULL) //extract a new sentence on the next line
		{
			for (int i = 0, j = 0, ii = 0; line[i] != '\0'; i++)
			{
				if (line[i] != ',') 
				{
					result_line[j][ii] = line[i];
					ii++;
				}
				
				else if (line[i] == ',')
				{
					j++;
					ii = 0; //! must reset zero
				}
				 
			}
			

			//for (int j = 0; j < 8; j++) if (result_line[j] == NULL) strcpy(result_line[j], "missing data");
			if (result_line[0][0] == '\0') strcpy(&result_line[0], "Missing ID");
			strcpy(fitbitdata_array[lineNum].patient, &result_line[0][0]);
			if (lineNum > 0 && strcmp(fitbitdata_array[lineNum].patient, "12cx7") != 0)
			{
				strcpy(fitbitdata_array[lineNum].patient, "");
				goto skip;
			} //different patient name record needs to be discarded!!!!!


			if (result_line[1][0] == '\0') strcpy(&result_line[1], "Missing Minute");
			strcpy(fitbitdata_array[lineNum].minute, &result_line[1][0]);
			if (lineNum > 0 && strcmp(fitbitdata_array[lineNum].minute, fitbitdata_array[lineNum - 1].minute) == 0)
			{
				strcpy(fitbitdata_array[lineNum].patient, "");
				strcpy(fitbitdata_array[lineNum].minute, "");
				goto skip;
			} //getting rid of duplicates!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			
			if (result_line[2][0] == '\0') strcpy(&result_line[2], "-1.00");
			fitbitdata_array[lineNum].calories = atof(&result_line[2][0]);

			if (result_line[3][0] == '\0') strcpy(&result_line[3], "-1.00");
			fitbitdata_array[lineNum].distance = atof(&result_line[3][0]);

			if (result_line[4][0] == '\0') strcpy(&result_line[4], "999");
			fitbitdata_array[lineNum].floors = atoi(&result_line[4][0]);

			if (result_line[5][0] == '\0') strcpy(&result_line[5], "999");
			fitbitdata_array[lineNum].heartRate = atoi(&result_line[5][0]);

			if (result_line[6][0] == '\0') strcpy(&result_line[6][0], "999");
			fitbitdata_array[lineNum].steps = atoi(&result_line[6][0]);

			if (result_line[7][0] == '\0' || result_line[7][0] == '\n') strcpy(&result_line[7][0], "-1\n"); // why adding 999\n????????????????????
			fitbitdata_array[lineNum].sleepLevel = atoi(&result_line[7][0]);


			/*printf("\n%s", &result_line[0]);
			printf("\n%s", &result_line[1]);
			printf("\n%s", &result_line[2]);
			printf("\n%s", &result_line[3]);
			printf("\n%s", &result_line[4]);
			printf("\n%s", &result_line[5]);
			printf("\n%s", &result_line[6]);
			printf("\n%s", &result_line[7]);*/

			lineNum++;

		skip:

			for (int i = 0; i < 100; i++) for (int j = 0; j < 8; j++) result_line[j][i] = '\0';
			//for (int i = 0; i < 8; i++) strcpy(&result_line[i][0], "");

		}

		printData(fitbitdata_array, 1440);

		////////////////////////////////////////////////////////////////////////////////
		printf("\n\n\n\n***********************  Interpreting the results  *************************************");

		double total_calories = 0.0; //invalid -1.00
		double total_distance = 0.0; //invalid -1.00
		unsigned int total_floors = 0.0; //invalid 999
		unsigned int total_steps = 0.0; //invalid 999
		//make sure for floors and steps unsigned int not double!!!! Reason why I kept geeting zero

		for (int i = 0; i < 1440; i++)
		{
			if (fitbitdata_array[i].calories != -1.00) total_calories += fitbitdata_array[i].calories;
			if (fitbitdata_array[i].distance != -1.00) total_distance += fitbitdata_array[i].distance;
			if (fitbitdata_array[i].floors != 999) total_floors += fitbitdata_array[i].floors;
			if (fitbitdata_array[i].steps != 999) total_steps += fitbitdata_array[i].steps;
		}

		printf("\n\nTotal Calories Burned: %lf Calories", total_calories);
		printf("\nTotal Distance Walked: %lf Miles", total_distance);
		printf("\nTotal Floors Walked: %u Floors", total_floors);
		printf("\nTotal Steps Taken: %u Steps", total_steps);
		//%u a format specifier for unsigned int!!!

		double total_heartRate = 0.0;
		double average_heartRate = 0.0;
		double initial_denominator = 1440.0;

		for (int i = 0; i < 1440; i++)
		{
			if (fitbitdata_array[i].heartRate != 999)
			{
				total_heartRate += fitbitdata_array[i].heartRate;
			}

			else if (fitbitdata_array[i].heartRate == 999)
			{
				--initial_denominator;
			}

		}
		average_heartRate = total_heartRate / initial_denominator;
		printf("\nAverage Heartrate: %lf", average_heartRate);
		unsigned int max_steps = 0;
		char time[100] = "";

		for (int i = 0; i < 1440; i++)
		{
			if (fitbitdata_array[i].steps >= max_steps) //>= the latest
			{
				max_steps = fitbitdata_array[i].steps;
				strcpy(time, fitbitdata_array[i].minute);
			}
		}

		printf("\nMax steps taken (latest time if multiple cases): %u steps at %s", max_steps, time);

		int poorestSleep_array[1440][2] = { {0,0}, {0,0} };
		int range_of_seconds = 0;
		int sum_of_sleepLevel = 0;
		int index = 0;
		char starting_time[1440][20] = { {""}, {""}};

		for (int i = 0; i < 1440; i++)
		{
			if (fitbitdata_array[i].sleepLevel == 2 || fitbitdata_array[i].sleepLevel == 3)
			{
				
				range_of_seconds++;
				sum_of_sleepLevel += fitbitdata_array[i].sleepLevel;
				for (int j = 1; fitbitdata_array[i + j].sleepLevel == 2 || fitbitdata_array[i + j].sleepLevel == 3; j++)
				{
					range_of_seconds++;
					sum_of_sleepLevel += fitbitdata_array[i + j].sleepLevel;
				} //consective ended

				strcpy(&starting_time[i], fitbitdata_array[i].minute);
				poorestSleep_array[i][0] = range_of_seconds;
				poorestSleep_array[i][1] = sum_of_sleepLevel;

				i = i + range_of_seconds; // 1 1 3 3 3 1

				range_of_seconds = 0;
				sum_of_sleepLevel = 0;
				//index++;
			}
		}

		int max_sum_of_sleepLevel = 0;
		int max_range_of_seconds = 0;
		char max_starting_time[20] = "";
		char max_ending_time[20] = "";

		for (int i = 0; i < 1440; i++)
		{
			if (max_sum_of_sleepLevel < poorestSleep_array[i][1])
			{
				max_sum_of_sleepLevel = poorestSleep_array[i][1];
				max_range_of_seconds = poorestSleep_array[i][0];
				strcpy(max_starting_time, starting_time[i]); //without the & this will naturally be converted to a ptr so will print out the string
				strcpy(max_ending_time, fitbitdata_array[i + max_range_of_seconds].minute);
			}                                                         ////////////-1!!!!!???????
		}

		
		printf("\n\nPoorest sleep time starts at: %s", max_starting_time);
		printf("\nPoorest sleep time finishes at: %s", max_ending_time);
		printf("\nThe range of seconds of the poorest sleep quality: %d seconds", max_range_of_seconds);

		FILE* result_file;
		result_file = fopen("Results.csv", "w");

		if (result_file != NULL)  //opened a new csv file successfully
		{
			fprintf(result_file, "Header line: Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n");
			fprintf(result_file, "%lf,%lf,%u,%u,%lf,%u,%s:%s\n", total_calories, total_distance, total_floors, total_steps, average_heartRate, max_steps, max_starting_time, max_ending_time);

			for (int i = 0; i < 1440; i++)
			{
				fprintf(result_file, "%s,", fitbitdata_array[i].patient);
				fprintf(result_file, "%s,", fitbitdata_array[i].minute);
				fprintf(result_file, "%lf,", fitbitdata_array[i].calories);
				fprintf(result_file, "%lf,", fitbitdata_array[i].distance);
				fprintf(result_file, "%u,", fitbitdata_array[i].floors);
				fprintf(result_file, "%u,", fitbitdata_array[i].heartRate);
				fprintf(result_file, "%u,", fitbitdata_array[i].steps);
				fprintf(result_file, "%d\n", fitbitdata_array[i].sleepLevel);


			}


		}

		else printf("\n\nResults.csv file failed to open");
		
		printf("\n\n******************************************************************************************\n");




		fclose(Patient_File);
		fclose(result_file);
		
		
	}

	else
	{
		printf("\nFile Not Opened!");
	}

	
	
	return 0;
}




//strcpy(fitbitdata_array[lineNum].minute, strtok(NULL, ","));
//fitbitdata_array[lineNum].calories = atof(strtok(NULL, ","));
//fitbitdata_array[lineNum].distance = atof(strtok(NULL, ","));
//fitbitdata_array[lineNum].floors = atoi(strtok(NULL, ","));
//fitbitdata_array[lineNum].heartRate = atoi(strtok(NULL, ","));
//fitbitdata_array[lineNum].steps = atoi(strtok(NULL, ","));
//fitbitdata_array[lineNum].sleepLevel = atoi(strtok(NULL, "\n"));
//
//lineNum++;




//strcpy(tempString, strtok(line, ","));
//if (tempString == '\n') strcpy(tempString, "missing ID");
//strcpy(fitbitdata_array[lineNum].patient, tempString);
//
//strcpy(tempString, strtok(NULL, ","));
//if (tempString == NULL) strcpy(tempString, "minute missing");
//strcpy(fitbitdata_array[lineNum].minute, tempString);
//
//strcpy(tempString, strtok(NULL, ","));
//if (tempString == NULL) strcpy(tempString, "-1.00");
//fitbitdata_array[lineNum].calories = atof(tempString);
//
//strcpy(tempString, strtok(NULL, ","));
//if (tempString == NULL) strcpy(tempString, "-1.00");
//fitbitdata_array[lineNum].distance = atof(tempString);
//
//strcpy(tempString, strtok(NULL, ","));
//if (tempString == NULL) strcpy(tempString, "999");
//fitbitdata_array[lineNum].floors = atoi(tempString);
//
//strcpy(tempString, strtok(NULL, ","));
//if (tempString == NULL) strcpy(tempString, "999");
//fitbitdata_array[lineNum].heartRate = atoi(tempString);
//
//strcpy(tempString, strtok(NULL, ","));
//if (tempString == NULL) strcpy(tempString, "999");
//fitbitdata_array[lineNum].steps = atoi(tempString);
//
//strcpy(tempString, strtok(NULL, ","));
//if (tempString == NULL) strcpy(tempString, "999");
//fitbitdata_array[lineNum].sleepLevel = atoi(tempString);

//
//
//for (int j = 0; j < 8; j++) if (result_line[j] == NULL) strcpy(result_line[j], "missing data");
//
//
//for (int j = 0; j < 8; j++)
//{
//	if (strcmp(result_line[j], "missing data") == 0) strcpy(fitbitdata_array[lineNum].patient, "Missing ID");
//	else strcpy(fitbitdata_array[lineNum].patient, result_line[j]);
//	j++;
//
//	if (strcmp(result_line[j], "missing data") == 0) strcpy(fitbitdata_array[lineNum].minute, "Missing Minute");
//	else strcpy(fitbitdata_array[lineNum].minute, result_line[j]);
//	j++;



//for (int j = 0; j < 8; j++)
//{
//	if (strcmp(result_line[j], "missing data") == 0) strcpy(fitbitdata_array[lineNum].patient, "Missing ID");
//	else strcpy(fitbitdata_array[lineNum].patient, result_line[j]);
//	j++;
//
//	if (strcmp(result_line[j], "missing data") == 0) strcpy(fitbitdata_array[lineNum].minute, "Missing Minute");
//	else strcpy(fitbitdata_array[lineNum].minute, result_line[j]);
//	j++;
//
//	strcpy(tempString, strtok(NULL, ","));
//	if (tempString == NULL) strcpy(tempString, "-1.00");
//	fitbitdata_array[lineNum].calories = atof(tempString);
//
//	strcpy(tempString, strtok(NULL, ","));
//	if (tempString == NULL) strcpy(tempString, "-1.00");
//	fitbitdata_array[lineNum].distance = atof(tempString);
//
//	strcpy(tempString, strtok(NULL, ","));
//	if (tempString == NULL) strcpy(tempString, "999");
//	fitbitdata_array[lineNum].floors = atoi(tempString);
//
//	strcpy(tempString, strtok(NULL, ","));
//	if (tempString == NULL) strcpy(tempString, "999");
//	fitbitdata_array[lineNum].heartRate = atoi(tempString);
//
//	strcpy(tempString, strtok(NULL, ","));
//	if (tempString == NULL) strcpy(tempString, "999");
//	fitbitdata_array[lineNum].steps = atoi(tempString);
//
//	strcpy(tempString, strtok(NULL, ","));
//	if (tempString == NULL) strcpy(tempString, "999");
//	fitbitdata_array[lineNum].sleepLevel = atoi(tempString);
//
//
//}