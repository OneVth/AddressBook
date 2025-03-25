#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"

void ClearInputBuffer(void)
{
	char ch = 0;
	while ((ch = getchar()) != '\n');
}

int IsAllDigit(const char* str)
{
	if (*str == '\0')
		return 0;

	while (*str != '\0')
	{
		if (!isdigit(*str))
			return 0;
		str++;
	}
	return 1;
}

int IsAllAlpha(const char* str)
{
	if (*str == '\0')
		return 0;

	while (*str != '\0')
	{
		if (!isalpha(*str))
			return 0;
		str++;
	}
	return 1;
}

int IsPhoneFormat(const char* str)
{
	if (*str == '\0')
		return 0;

	return ((strlen(str) == 13) && (str[3] == '-') && (str[8] == '-') ? 1 : 0);
}

void InitList(LIST* pL)
{
	pL->head.next = &pL->tail;
	pL->head.prev = NULL;
	pL->tail.next = NULL;
	pL->tail.prev = &pL->head;
}

void ReleaseList(LIST* pL)
{
	if (IsEmpty(pL))
		return;

	NODE* ptr = pL->head.next;
	while (ptr != &pL->tail)
	{
		NODE* del = ptr;
		ptr = ptr->next;
		free(del);
	}
}

int IsEmpty(LIST* pL)
{
	if (pL->head.next == &pL->tail)
		return 1;

	return 0;
}

int InsertNodeAtBeg(LIST* pL, const int age, const char* name, const char* phone)
{
	if (pL == NULL)
		return 0;

	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->age = age;
	strcpy_s(newNode->name, sizeof(newNode->name), name);
	strcpy_s(newNode->phone, sizeof(newNode->phone), phone);

	NODE* ptr = pL->head.next;
	newNode->next = ptr;
	newNode->prev = &pL->head;
	pL->head.next = newNode;
	ptr->prev = newNode;

	return 1;
}

int InsertNodeAtEnd(LIST* pL, const int age, const char* name, const char* phone)
{
	if (pL == NULL)
		return 0;

	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->age = age;
	strcpy_s(newNode->name, sizeof(newNode->name), name);
	strcpy_s(newNode->phone, sizeof(newNode->phone), phone);

	NODE* ptr = pL->tail.prev;
	newNode->next = &pL->tail;
	newNode->prev = ptr;
	ptr->next = newNode;
	pL->tail.prev = newNode;

	return 1;
}

int DeleteNodeAtEnd(LIST* pL)
{
	if (IsEmpty(pL))
		return 0;

	NODE* ptr = pL->tail.prev;
	ptr->prev->next = &pL->tail;
	pL->tail.prev = ptr->prev;

	free(ptr);
	return 1;
}

int DeleteNodeAtBeg(LIST* pL)
{
	if (IsEmpty(pL))
		return 0;

	NODE* ptr = pL->head.next;
	ptr->next->prev = &pL->head;
	pL->head.next = ptr->next;

	free(ptr);
	return 1;
}

int DeleteNodeByPhone(LIST* pL, const char* phone)
{
	if (IsEmpty(pL))
		return 0;

	NODE* ptr = pL->head.next;
	while (ptr != &pL->tail)
	{
		if (strcmp(ptr->phone, phone) == 0)
		{
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
			free(ptr);
			return 1;
		}
		ptr = ptr->next;
	}
	return 0;
}

int HasPhoneInList(LIST* pL, const char* phone)
{
	NODE* ptr = pL->head.next;
	while (ptr != &pL->tail)
	{
		if (strcmp(ptr->phone, phone) == 0)
			return 1;

		ptr = ptr->next;
	}

	return 0;
}

int CombineList(LIST* pResultList, LIST* pList1, LIST* pList2, const char* op)
{
	NODE* ptr1 = pList1->head.next;
	NODE* ptr2 = pList2->head.next;

	if (strcmp(op, "OR") == 0 || strcmp(op, "or") == 0)
	{
		while (ptr1 != &pList1->tail)
		{
			InsertNodeAtEnd(pResultList, ptr1->age, ptr1->name, ptr1->phone);
			ptr1 = ptr1->next;
		}

		while (ptr2 != &pList2->tail)
		{
			if (!HasPhoneInList(pResultList, ptr2->phone))
			{
				InsertNodeAtEnd(pResultList, ptr2->age, ptr2->name, ptr2->phone);
			}
			ptr2 = ptr2->next;
		}
	}
	else if (strcmp(op, "AND") == 0 || strcmp(op, "and") == 0)
	{
		while (ptr1 != &pList1->tail)
		{
			if (HasPhoneInList(pList2, ptr1->phone))
			{
				InsertNodeAtEnd(pResultList, ptr1->age, ptr1->name, ptr1->phone);
			}
			ptr1 = ptr1->next;
		}
	}
	else
	{
		return 0;
	}

	return 1;
}