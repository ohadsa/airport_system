#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Company.h"
#include "AirportManager.h"
#include "General.h"

/*
Ohad  Saada 204624209
liron Shish 315238915
*/
typedef enum 
{ 
	eAddFlight, eAddAirport, ePrintCompany, ePrintAirports,
	ePrintFlightOrigDest,eSortFlights, eSearchFlight, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Flight", "Add Airport",
								"PrintCompany", "Print all Airports",
								"Print flights between origin-destination"
								,"Sort flights by parameter" , "Search flight"
								};

#define EXIT			-1
int menu();

int main()
{
	AirportManager	manager;
	Company			company;

	FILE* txtFile = fopen("airport_authority.txt", "r");
	FILE* binFile = fopen("company.bin", "rb");

	if (!txtFile || !binFile)  //If the file not exist
	{
		initManager(&manager);
		initCompany(&company);
	}
	else
	{
		initAirportManagerFromTextFile(txtFile, &manager);
		initCompanyFromBinaryFile(binFile, &company);
	}
	int option;
	int stop = 0;
	
	do
	{
		option = menu();
		switch (option)
		{
		case eAddFlight:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			break;


		case eAddAirport:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			break;

		case ePrintCompany:
			printCompany(&company);
			break;

		case ePrintAirports:
			printAirports(&manager);
			break;

		case ePrintFlightOrigDest:
			printFlightsCount(&company);
			break;

		case eSortFlights:
			sortFlightsByParameter(&company);
			break;
		case eSearchFlight:
			searchFlightByParameter(&company);
			break;

		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);
	FILE* writeTxtFile = fopen("airport_authority.txt", "w");
	FILE* writeBinFile = fopen("company.bin", "wb");
	writeAirportmanagerToTextFile(writeTxtFile, &manager);
	writeCompanyToBinaryFile(writeBinFile, &company);
	freeManager(&manager);
	freeCompany(&company);
	system("pause");
	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for(int i = 0 ; i < eNofOptions ; i++)
		printf("%d - %s\n",i,str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}