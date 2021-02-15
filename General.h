#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255
#define CODE_LENGTH 3

char*	getStrExactName(const char* msg);
char*	myGets(char* buffer, int size);
char*	getDynStr(char* str);
char**	splitCharsToWords(char* str,int* pCount,int* pTotalLength);
void myQsort(void** arr, size_t numOfElements, size_t sizeOfElement , int(*compare)(const void*,const void*));
void fixStr(char* str);
int readStringFromTextFile(FILE* file, char* buffer); 
int readIntFromTextFile(FILE* file, int* buffer); //return 1 if succeeded
void generalArrayFunction(void **arr, size_t numOfElements, size_t sizeOfEachElement, void(*func)(void*));
#endif


