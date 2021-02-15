#ifndef __MYDATE__
#define __MYDATE__

#define MIN_YEAR 2020

typedef struct
{
	int			day;
	int			month;
	int			year;
}Date;

void	getCorrectDate(Date* pDate);
int		checkDate(char* date, Date* pDate);
void	printDate(const Date* pDate);
int		compareDate(const void* date1, const void* date2);
void	freeDate(void* date);
void	writeDateToBinFile(FILE *file, Date *date);

#endif
