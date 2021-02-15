
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listGen.h"
#include "Airport.h"
#include "Date.h"

BOOL L_init(LIST* pList)
{
	if (pList == NULL) return False;	// no list to initialize

	pList->head = NULL;
	return True;
}

NODE* L_insert(NODE* pNode, DATA Value)
{
	NODE* tmp;

	if (!pNode) 
		return NULL;

	tmp = (NODE*)malloc(sizeof(NODE));	// new node

	if (tmp != NULL) {
		tmp->key = Value;
		tmp->next = pNode->next;
		pNode->next = tmp;
	}
	return tmp;
}
int L_insertFirstNode(LIST* pList, DATA value)
{
	NODE* tmp;
	if (!pList)
	{
		return 0;
	}

	tmp = (NODE*)malloc(sizeof(NODE));	// new node

	if (tmp != NULL) {
		tmp->key = value;
		pList->head = tmp;
		pList->head->next = NULL;
	}
	return 1;
}

BOOL L_delete(NODE* pNode, void(*freeFunc)(void*))
{
	NODE* tmp;

	if (!pNode || !(tmp = pNode->next)) return False;

	pNode->next = tmp->next;
	if (freeFunc != NULL)
		freeFunc(tmp->key);
	free(tmp);
	return True;
}

int L_find(NODE* pNode, DATA value, int(*compare)(const void*, const void*))
{
	if (!pNode)
		return 0;
	while (pNode)
	{	
		if (compare(pNode->key, value) == 0)
			return 1;
		pNode = pNode->next;
	}
	return 0;
}

BOOL L_free(LIST* pList, void(*freeFunc)(void*))
{
	NODE *tmp;

	if (!pList) return False;
	tmp = (pList->head);
	BOOL res = True;
	while (res)
	{
		res = L_delete(tmp, freeFunc);
	}

	return True;
}

int L_print(LIST* pList, void(*print)(const void*))
{
	NODE	*tmp;
	int		c = 0;

	if (!pList) return 0;

	printf("\n");
	for (tmp = pList->head; tmp; tmp = tmp->next, c++)
		print(tmp->key);
	printf("\n");
	return c;
}

void L_Sort(LIST* list, int(*compare)(void*, void*))
{
	NODE* temp1;
	NODE* temp2;
	for (temp1 = list->head; temp1 != NULL; temp1 = temp1->next)
	{
		for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next)
		{
			if (compare(temp2->key, temp1->key) < 0)
			{
				L_swap(temp1, temp2);
			}
		}
	}
}

void L_swap(NODE* n1, NODE* n2)
{
	DATA a;
	a = n1->key;
	n1->key = n2->key;
	n2->key = a;
}