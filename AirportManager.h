#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__

#include "Airport.h"
#include "listGen.h"
typedef struct
{
	LIST	airportList;
	int			count;
}AirportManager;

int		initManager(AirportManager* pManager);
int		addAirport(AirportManager* pManager);
void	setAirport(Airport* pPort, AirportManager* pManager);
Airport* findAirportByCode(AirportManager* pManager, const char* code);
int		checkUniqeCode(const char* code, AirportManager* pManager);
void	printAirports(AirportManager* pManager);
void	freeManager(AirportManager* pManager);
void	initAirportManagerFromTextFile(FILE* file, AirportManager* pManager);
void	writeAirportmanagerToTextFile(FILE *file, AirportManager* pManager);
#endif