#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"
#include "listGen.h"
typedef enum
{
	eNotSorted, eSortByHour, eSortByDate, eSortByOriginCode, eSortByDestinationCode, eNumOfOptions
}eSortOption;

typedef struct
{
	char*		name;
	int			flightCount;
	Flight**	flightArr;
	LIST		dateList;
	eSortOption sortType;
}Company;

void	initCompany(Company* pComp);
int		addFlight(Company* pComp,AirportManager* pManager);
void	printCompany(Company* pComp);
void	printFlightsCount(const Company* pComp);
void	freeCompany(Company* pComp);
void	sortFlightsByParameter(Company* pCompany);
void	chooseParameter(Company* pCompany);
void	addFlightDateToDateList(Company* pComp, Date* date);
void	initCompanyFromBinaryFile(FILE* file, Company* pCompany);
void	writeCompanyToBinaryFile(FILE *file, Company *pComp);
void	searchFlightByParameter(Company *pComp);

#endif

