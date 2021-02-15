#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Flight.h"
#include "General.h"



char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	printf("%s\t", msg);
	myGets(temp, MAX_STR_LEN);

	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}



char*  myGets(char* buffer, int size)
{
	if (buffer != NULL && size > 0)
	{
		if (fgets(buffer, size, stdin))
		{
			buffer[strcspn(buffer, "\n")] = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

char**	splitCharsToWords(char* str, int* pCount, int* pTotalLength)
{
	char temp[255];
	char* delimiters = " ";
	char* word;
	int count = 0;

	strcpy(temp, str);
	char** wordsArray = NULL;
	*pTotalLength = 0;

	word = strtok(temp, delimiters);
	while (word != NULL)
	{
		wordsArray = (char**)realloc(wordsArray,(count + 1)*sizeof(char*));
		if (!wordsArray)
			return 0;
		wordsArray[count] = getDynStr(word);
		count++;
		*pTotalLength += (int)strlen(word);
		word = strtok(NULL, delimiters);
	}
	*pCount = count;
	return wordsArray;
}

void myQsort(void** arr, size_t numOfElements, size_t sizeOfElement, int(*compare)(const void*,const void*))
{
	int i, j;
	void* temp;
	for (i = 0; i < numOfElements - 1 ; ++i)
	{
		for (j = 0; j < numOfElements - i - 1 ; ++j)
		{
			if (compare((arr+j) , (arr + j + 1)) > 0 )
			{
				temp = *(arr + j + 1);
				*(arr + j + 1)  =  *(arr + j ) ;
				*(arr + j ) = temp;
			}
		}
	}
	
}
void fixStr(char* str)
{
	char* temp = str;
	int count = 0;
	while (*temp != '\n')
	{
		count++;
		temp++;
	}
	str[count] = '\0';
}


int readStringFromTextFile(FILE* file, char* buffer)
{
	char temp[MAX_STR_LEN];
	if (fgets(temp, MAX_STR_LEN, file) == NULL)
		return 0;
	fixStr(temp);
	strcpy(buffer, temp);
	return 1;
}
int readIntFromTextFile(FILE* file, int* buffer)
{
	char tav;
	if (fscanf(file, "%d", buffer) == 0)
		return 0;
	fscanf(file, "%c", &tav);
	return 1;
}

void generalArrayFunction(void **arr, size_t numOfElements, size_t sizeOfEachElement, void(*func)(void*))
{
	char** tmp = (char**)arr;
	for (int i = 0; i < numOfElements; i ++)
	{	
		
		func(*(tmp + i ));
		
	}
}