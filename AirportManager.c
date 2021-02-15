#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AirportManager.h"

void initAirportManagerFromTextFile(FILE* file, AirportManager* pManager)
{
	
	pManager->count = 0;
	L_init(&(pManager->airportList));
	int numOfAirpoets;
	readIntFromTextFile(file, &numOfAirpoets);
	for (int i = 0; i < numOfAirpoets; i++)
	{
		Airport* airport = (Airport*)malloc(sizeof(Airport));
		if (readAirportFromTextFile(file, airport) == 0)
		{
			fclose(file);
			return;
		}
		if (pManager->count == 0) 
		{
			L_insertFirstNode(&pManager->airportList, airport);
			pManager->count = 1;
		}
		else 
		{
			L_insert(pManager->airportList.head, airport);
			pManager->count++;
		}
	}
	L_Sort(&pManager->airportList, compareAirportByIATA);
	fclose(file);
}


int	initManager(AirportManager* pManager)
{
	printf("-----------  Init airport Manager\n");
	pManager->count = 0;
	L_init(&(pManager->airportList));

	int count = 0;
	do {
		printf("How many airport?\t");
		scanf("%d", &count);
	} while (count < 0);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	if (count == 0)
		return 1;

	for (int i = 0; i < count; i++)
	{
		addAirport(pManager);
	}

	return 1;
}

int	addAirport(AirportManager* pManager)
{
	Airport* airport = (Airport*)malloc(sizeof(Airport));
	if (!airport)
		return 0;
	setAirport(airport, pManager);
	NODE* pNode = (pManager->airportList.head);
	if (pManager->count == 0)
	{
		if ((L_insertFirstNode(&pManager->airportList, airport))==0)
		{
			freeAirport(airport);
			return 0;
		}
		pManager->count = 1;
		L_Sort(&(pManager->airportList), compareAirportByIATA);
		return 1;
	}
	else
	{
		if (!(L_insert(pNode, airport)))
		{
			freeAirport(airport);
			return 0;
		}
		pManager->count++;
		L_Sort(&(pManager->airportList), compareAirportByIATA);
		return 1;
	}
}


void  setAirport(Airport* pPort, AirportManager* pManager)
{
	while (1)
	{
		getAirportCode(pPort->code);
		if (checkUniqeCode(pPort->code, pManager))
			break;
		printf("This code already in use - enter a different code\n");
	}
	initAirportNoCode(pPort);
}

Airport* findAirportByCode(AirportManager* pManager, const char* code)
{
	NODE* pNext = (pManager->airportList.head);
	while (pNext != NULL)
	{
		if (isAirportCode((Airport*)pNext->key, code))
			return (Airport*)pNext->key;
		pNext = pNext->next;
	}
	return NULL;
}


int checkUniqeCode(const char* code,AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager, code);

	if (port != NULL)
		return 0;

	return 1;
}

void	printAirports(AirportManager* pManager)
{
	printf("there are %d airports\n", pManager->count);
	L_print(&(pManager->airportList), printAirport);
}

void	freeManager(AirportManager* pManager)
{
	L_free(&(pManager->airportList), freeAirport);
}

void	writeAirportmanagerToTextFile(FILE *file, AirportManager* pManager)
{
	if (!file)
	{
		fclose(file);
		return;
	}
	fprintf(file, "%d\n",pManager->count);
	NODE* pNode = pManager->airportList.head;
	for (int i = 0; i < pManager->count; i++)
	{
		writeAirportToTextFile(file , pNode->key);
		pNode = pNode->next;
	}
	fclose(file);
}
