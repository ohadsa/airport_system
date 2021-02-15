
#ifndef _LIST_
#define _LIST_

#include "def.h"

// Node
typedef struct node
{
	DATA			key;
	struct node*	next;
}NODE;

// List
typedef struct
{
	NODE *head;
}LIST;


BOOL L_init(LIST* pList);					

NODE* L_insert(NODE* pNode, DATA Value);	

BOOL L_delete(NODE* pNode, void(*freeFunc)(void*));					

int L_find(NODE* pNode, DATA value, int(*compare)(const void*, const void*));		

BOOL L_free(LIST* pList, void(*freeFunc)(void*));					

int L_print(LIST* pList, void(*print)(const void*));				

void L_Sort(LIST* list, int(*compare)(void*, void*));

void L_swap(NODE* n1, NODE* n2);

int L_insertFirstNode(LIST* pNode, DATA value);

#endif
