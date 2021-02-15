#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Company.h"
#include "Airport.h"
#include "General.h"
#include "Date.h"

int(*compares[eNumOfOptions])(const void*,const void*) = {
	dontCompareFlights , compareFlightByHour , compareFlightByDate , compareFlightByOriginCode , compareFlightByDestinationCode 
};

void	initCompany(Company* pComp)
{
	printf("-----------  Init Airline Company\n");
	pComp->name = getStrExactName("Enter company name");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	L_init(&(pComp->dateList));
	pComp->sortType = 0;
}
int	addFlight(Company* pComp,AirportManager* pManager)
{
	if (pManager->count < 2)
	{
		printf("There are not enoght airport to set a flight\n");
		return 0;
	}
	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount+1) * sizeof(Flight*));
	if (!pComp->flightArr)
		return 0;
	pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1,sizeof(Flight));
	if (!pComp->flightArr[pComp->flightCount])
		return 0;
	initFlight(pComp->flightArr[pComp->flightCount],pManager);
	addFlightDateToDateList(pComp, &pComp->flightArr[pComp->flightCount]->date);
	pComp->flightCount++;
	myQsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compares[pComp->sortType]);
	return 1;

}
void addFlightDateToDateList(Company* pComp, Date* date)
{
	if (pComp->flightCount == 0)
	{
		L_insertFirstNode(&(pComp->dateList), date);
		return;
	}
	if(L_find((pComp->dateList.head),date,compareDate)==0)
		L_insert((pComp->dateList.head), date);
}



void printCompany(Company* pComp)
{
	printf("Company %s:\n", pComp->name);
	printf("Has %d flights\n",pComp->flightCount);
	//using generic func to print the flight arr
	generalArrayFunction(pComp->flightArr, pComp->flightCount, sizeof(Flight*), printFlight);
	if(pComp->flightCount != 0 )
		printf("there is flight in dates :");
	L_print(&pComp->dateList , printDate);
}

void	printFlightsCount(const Company* pComp)
{
	char codeOrigin[CODE_LENGTH+1];
	char codeDestination[CODE_LENGTH + 1];
	
	if (pComp->flightCount == 0)
	{
		printf("No flight to search\n");
		return;
	}

	printf("Origin Airport\n");
	getAirportCode(codeOrigin);
	printf("Destination Airport\n");
	getAirportCode(codeDestination);

	int count = countFlightsInRoute(pComp->flightArr, pComp->flightCount, codeOrigin, codeDestination);
	if (count != 0)
		printf("There are %d flights ", count);
	else
		printf("There are No flights ");

	printf("from %s to %s\n",codeOrigin, codeDestination);
}



void	freeCompany(Company* pComp)
{
	//using generic arr function to free flight arr
	generalArrayFunction(pComp->flightArr, pComp->flightCount, sizeof(Flight*), freeFlight);
	free(pComp->flightArr);
	free(pComp->name);
	L_free(&pComp->dateList , freeDate);
}

void	sortFlightsByParameter(Company* pCompany)
{
	if (pCompany->flightCount == 0)
	{
		printf("there is no flights to sort\n");
		return;
	}
	int choose;
	chooseParameter(pCompany);
	choose = pCompany->sortType;
	myQsort(pCompany->flightArr, pCompany->flightCount, sizeof(Flight*), compares[choose]);
	
}
void chooseParameter(Company* pCompany)
{
	char* options[eNumOfOptions] = { "no sort","sort by hour","sort by date","sort by Origin code","sort by Destination code" };
	do 
	{
		printf("How would you like to sort the array?\n");
		for (int i = 0;i < eNumOfOptions;i++)
			printf("%d - %s\n", i, options[i]);
		scanf("%d", &pCompany->sortType);
		char tav;
		scanf("%c", &tav);
	} while (pCompany->sortType < 0  || pCompany->sortType > 4);
}
void initCompanyFromBinaryFile(FILE* file, Company* pComp)
{
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	L_init(&(pComp->dateList));
	int nameLen , numOfFlights;
	fread(&nameLen, sizeof(int), 1, file);
	pComp->name = (char*)malloc(sizeof(char)*nameLen);
	if (!pComp->name)
	{
		fclose(file);
		return;
	}
	fread(pComp->name, sizeof(char), nameLen, file);
	fread(&numOfFlights, sizeof(int), 1, file);
	fread(&pComp->sortType, sizeof(int), 1, file);
	for (int i = 0; i < numOfFlights; i++)
	{
		pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
		pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1, sizeof(Flight));
		readFlightFromBinFile(file, pComp->flightArr[pComp->flightCount]);
		addFlightDateToDateList(pComp, &pComp->flightArr[pComp->flightCount]->date);
		pComp->flightCount++;
		
	}
	if(pComp->flightCount >= 2)
		myQsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compares[pComp->sortType]);
}

void writeCompanyToBinaryFile(FILE *file, Company *pComp)
{
	int nameLen = (int)strlen(pComp->name) + 1;
	fwrite(&nameLen, sizeof(int), 1, file);
	fwrite(pComp->name, sizeof(char), strlen(pComp->name) + 1, file);
	fwrite(&pComp->flightCount, sizeof(int), 1, file);
	fwrite(&pComp->sortType, sizeof(int), 1, file);
	for (int i = 0; i < pComp->flightCount; i++)
	{
		writeFlightToBinFile(file, pComp->flightArr[i]);
	}
	fclose(file);
}

void searchFlightByParameter(Company *pComp)
{
	int hour = 0;
	Date date = { 0,0,0 };
	char origin[CODE_LENGTH+1] = "";
	char dest[CODE_LENGTH+1] = "";
	switch (pComp->sortType)
	{
	case eSortByHour:
		hour = getFlightHour();
		break; 
	case eSortByDate:
		getCorrectDate(&date);
		break;
	case eSortByOriginCode:
		getAirportCode(origin);
		break;
	case eSortByDestinationCode:
		getAirportCode(dest);
		break;
	}
	Flight *flight = (Flight*)malloc(sizeof(Flight));
	setFlightByParameter(flight, origin, dest,hour, &date);
	Flight** result = (Flight**)(bsearch(&flight, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compares[pComp->sortType]));
	freeFlight(flight);
	if (result)
		printFlight(*result);
	else
		printf("Not found.\n");
}