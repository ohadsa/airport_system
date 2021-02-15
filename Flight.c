#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flight.h"
#include "General.h"

void	initFlight(Flight* pFlight,AirportManager* pManager)
{
	Airport* pPortOr = setAiportToFlight(pManager,"Enter code of origin airport:");
	strcpy(pFlight->originCode, pPortOr->code);
	int same;
	Airport* pPortDes;
	do {
		pPortDes = setAiportToFlight(pManager,"Enter code of destination airport:");
		same = isSameAirport(pPortOr, pPortDes);
		if (same)
			printf("Same origin and destination airport\n");
	} while (same);
	strcpy(pFlight->destCode, pPortDes->code);
	getCorrectDate(&pFlight->date);
	pFlight->hour = getFlightHour();
}

int	isFlightInRoute(const Flight* pFlight,const char* codeSource, const char* codeDest)
{
	if ((strcmp(pFlight->originCode, codeSource) == 0) &&
		(strcmp(pFlight->destCode, codeDest) == 0))
		return 1;

	return 0;
}

int	countFlightsInRoute(Flight** arr, int size,const char* codeSource, 
		const char* codeDest)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (isFlightInRoute(arr[i], codeSource, codeDest))
			count++;
	}
	return count;
}

void	printFlight(void* pFlight)
{
	Flight* pF = (Flight*)pFlight;
	printf("Flight From %s To %s\t",pF->originCode, pF->destCode);
	printDate(&pF->date);
	printf("Hour: %d\n",pF->hour);
}


int getFlightHour()
{
	int h;
	do {
		printf("Enter flight hour [0-23]:\t");
		scanf("%d", &h);
	} while (h < 0 || h>23);
	return h;
}

Airport* setAiportToFlight(AirportManager* pManager, const char* msg)
{
	char code[MAX_STR_LEN];
	Airport* port;
	do
	{
		printf("%s\t", msg);
		myGets(code, MAX_STR_LEN);
		port = findAirportByCode(pManager, code);
		if (port == NULL)
			printf("No airport in this country - try again\n");
	} while(port == NULL);

	return port;

}

void	freeFlight(Flight* pFlight)
{
	free(pFlight);
}

int compareFlightByHour(const void* flight1, const void* flight2)
{
	Flight** f1 = (Flight**)flight1;
	Flight** f2 = (Flight**)flight2;
	return ((*f1)->hour - (*f2)->hour);
	
}
int compareFlightByDate(const void* flight1, const void* flight2)
{
	Flight** f1 = (Flight**)flight1;
	Flight** f2 = (Flight**)flight2;
	return compareDate(&(*f1)->date, &(*f2)->date);
}
int compareFlightByOriginCode(const void* flight1, const void* flight2)
{
	Flight** f1 = (Flight**)flight1;
	Flight** f2 = (Flight**)flight2;
	return strcmp((*f1)->originCode, (*f2)->originCode);
}
int compareFlightByDestinationCode(const void* flight1, const void* flight2)
{
	Flight** f1 = (Flight**)flight1;
	Flight** f2 = (Flight**)flight2;
	return strcmp((*f1)->destCode, (*f2)->destCode);
}
int dontCompareFlights(const void* n1,const void* n2) {//for using generic function array
	return 0;
}

void writeFlightToBinFile(FILE *file, Flight* flight)
{
	fwrite(flight->originCode, sizeof(char), CODE_LENGTH + 1, file);
	fwrite(flight->destCode, sizeof(char), CODE_LENGTH + 1, file);
	fwrite(&flight->hour, sizeof(int), 1, file);
	writeDateToBinFile(file, &flight->date);
}
void readFlightFromBinFile(FILE *file, Flight *flight)
{
	fread(flight->originCode, sizeof(char), CODE_LENGTH + 1, file);
	fread(flight->destCode, sizeof(char), CODE_LENGTH + 1, file);
	fread(&flight->hour, sizeof(int), 1, file);
	fread(&flight->date, sizeof(Date), 1, file);
}

void	setFlightByParameter(Flight* flight , char* origin, char* dest, int hour, Date* date)
{
	flight->hour = hour;
	flight->date = *date;
	strcpy(flight->originCode, origin);
	strcpy(flight->destCode, dest);
}