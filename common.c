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

int Str_IsAllDigit(const char* str)
{
	if (str == NULL)
		return 0;

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

int Str_IsAllAlpha(const char* str)
{
	if (str == NULL)
		return 0;

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

int Str_IsPhoneFormat(const char* str)
{
	if (str == NULL)
		return 0;

	if (*str == '\0')
		return 0;

	if (strlen(str) != 13)
		return 0;

	int i = 0;
	while (i != 12)
	{
		if (i == 3 || i == 8)
		{
			if (str[i++] != '-')
				return 0;
		}

		if (!isdigit(str[i++]))
			return 0;
	}

	return 1;
}

int ClassifyToken(const char* token, int* age, char* name, char* phone)
{
	if (Str_IsAllDigit(token))
	{
		*age = atoi(token);
		if (*age < 0 || *age > MAXAGE)
			return 0;
	}
	else
	{
		if (Str_IsAllAlpha(token))
			strcpy_s(name, MAX_NAME_LEN, token);
		else if (Str_IsPhoneFormat(token))
			strcpy_s(phone, MAX_PHONE_LEN, token);
		else
			return 0;
	}
	return 1;
}

int SplitSearchExpression(const char* input, char token1[], char token2[], char op[])
{
	int i = 0;
	const char* ch = input;
	while (*ch != '\0')
	{
		if (*ch == ' ')
		{
			ch++;
			break;
		}
		token1[i++] = *ch;
		ch++;
	}
	token1[i] = '\0';

	i = 0;
	while (*ch != '\0')
	{
		if (*ch == ' ')
		{
			ch++;
			break;
		}

		op[i++] = *ch;
		ch++;
	}
	op[i] = '\0';

	i = 0;
	while (*ch != '\0')
	{
		token2[i++] = *ch;
		ch++;
	}
	token2[i] = '\0';

	if ((token1[0] != 0 && op[0] == 0 && token2[0] == 0) ||
		(token1[0] != 0 && op[0] != 0 && token2[0] != 0))
	{
		return 1;
	}
	else
		return 0;
}

void List_Init(LIST* pL)
{
	pL->head.next = &pL->tail;
	pL->head.prev = NULL;
	pL->tail.next = NULL;
	pL->tail.prev = &pL->head;
}

void List_Release(LIST* pL)
{
	if (List_IsEmpty(pL))
		return;

	NODE* ptr = pL->head.next;
	while (ptr != &pL->tail)
	{
		NODE* del = ptr;
		ptr = ptr->next;
		free(del);
	}

	List_Init(pL);
}

int List_IsEmpty(LIST* pL)
{
	if (pL->head.next == &pL->tail)
		return 1;

	return 0;
}

int List_InsertAtBeg(LIST* pL, const int age, const char* name, const char* phone)
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

int List_InsertAtEnd(LIST* pL, const int age, const char* name, const char* phone)
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

int List_DeleteAtEnd(LIST* pL)
{
	if (List_IsEmpty(pL))
		return 0;

	NODE* ptr = pL->tail.prev;
	ptr->prev->next = &pL->tail;
	pL->tail.prev = ptr->prev;

	free(ptr);
	return 1;
}

int List_DeleteAtBeg(LIST* pL)
{
	if (List_IsEmpty(pL))
		return 0;

	NODE* ptr = pL->head.next;
	ptr->next->prev = &pL->head;
	pL->head.next = ptr->next;

	free(ptr);
	return 1;
}

int List_DeleteByPhone(LIST* pL, const char* phone)
{
	if (List_IsEmpty(pL))
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

int List_HasPhone(LIST* pL, const char* phone)
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

int List_CombineByOp(LIST* pResultList, LIST* pList1, LIST* pList2, const char* op)
{
	NODE* ptr1 = pList1->head.next;
	NODE* ptr2 = pList2->head.next;

	if (strcmp(op, "OR") == 0 || strcmp(op, "or") == 0)
	{
		while (ptr1 != &pList1->tail)
		{
			List_InsertAtEnd(pResultList, ptr1->age, ptr1->name, ptr1->phone);
			ptr1 = ptr1->next;
		}

		while (ptr2 != &pList2->tail)
		{
			if (!List_HasPhone(pResultList, ptr2->phone))
			{
				List_InsertAtEnd(pResultList, ptr2->age, ptr2->name, ptr2->phone);
			}
			ptr2 = ptr2->next;
		}
	}
	else if (strcmp(op, "AND") == 0 || strcmp(op, "and") == 0)
	{
		while (ptr1 != &pList1->tail)
		{
			if (List_HasPhone(pList2, ptr1->phone))
			{
				List_InsertAtEnd(pResultList, ptr1->age, ptr1->name, ptr1->phone);
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

