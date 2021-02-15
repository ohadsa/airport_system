#ifndef __FLIGHT__
#define __FLIGHT__

#include "AirportManager.h"
#include "Date.h"
#include "General.h"

typedef struct
{
	char		originCode[CODE_LENGTH + 1];
	char		destCode[CODE_LENGTH + 1];
	int			hour;
	Date		date;
}Flight;

void	initFlight(Flight* pFlight,AirportManager* pManager);
int		isFlightInRoute(const Flight* pFlight, const char* codeSource, const char* codeDest);
int		countFlightsInRoute(Flight** arr, int size,const char* codeSource, const char* codeDest);
void	printFlight( void *pFlight);
int		getFlightHour();
Airport*	setAiportToFlight(AirportManager* pManager, const char* msg);
void	freeFlight(Flight* pFlight);
int		compareFlightByHour(const void* flight1, const void* flight2);
int		compareFlightByDate(const void* flight1, const void* flight2);
int		compareFlightByOriginCode(const void* flight1, const void* flight2);
int		compareFlightByDestinationCode(const void* flight1, const void* flight2);
int		dontCompareFlights(const void* n1, const void* n2);
void	writeFlightToBinFile(FILE *file, Flight* flight);
void	readFlightFromBinFile(FILE *file, Flight *flight);
void	setFlightByParameter(Flight* flight ,char* origin, char* dest, int hour, Date* date);
#endif
