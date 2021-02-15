#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "General.h"
#include "Date.h"

const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };


void getCorrectDate(Date* pDate)
{
	char date[MAX_STR_LEN];
	int ok = 1;

	do {
		puts("Enter Flight Date dd/mm/yyyy\t");
		myGets(date, MAX_STR_LEN);
		ok = checkDate(date, pDate);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);
}


int	 checkDate(char* date, Date* pDate)
{
	int day, month, year;
	if (strlen(date) != 10)
		return 0;
	if ( (date[2] != '/') || (date[5] != '/'))
		return 0;
	sscanf(date, "%d/%d/%d", &day, &month, &year);
	if (day < 1 || month < 1 || month > 12 || year < MIN_YEAR)
		return 0;

	if (day > DAY_MONTHS[month - 1])
		return 0;

	pDate->day = day;
	pDate->month = month;
	pDate->year = year;

	return 1;
}

void printDate(const Date* pDate)
{
	printf("Date: %d/%d/%d\n", pDate->day, pDate->month, pDate->year);
}
void freeDate(void* date) // to use generic free function to free date 
{
	return;
}
int compareDate(const void* date1,const void* date2)
{
	Date* d1 = (Date*)date1;
	Date* d2 = (Date*)date2;

	int compare = d1->year - d2->year;

	if (compare == 0)
	{
		compare = d1->month - d2->month;
		if (compare == 0)
		{
			compare = d1->day - d2->day;
		}
	}
	return compare;
}


void readDateFromBinFile(FILE *file, Date* date)
{
	fread(&date->day, sizeof(int), 1, file);
	fread(&date->month, sizeof(int), 1, file);
	fread(&date->year, sizeof(int), 1, file);
}
void writeDateToBinFile(FILE *file, Date *date)
{
	fwrite(&date->day, sizeof(int),  1, file);
	fwrite(&date->month, sizeof(int), 1, file);
	fwrite(&date->year, sizeof(int), 1, file);
}