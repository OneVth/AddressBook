#include <stdio.h>
#include "contact.h"

//struct _Contact {
//	int age;
//	char name[MAX_NAME_LEN];
//	char phone[MAX_PHONE_LEN];
//};

const char* Contact_GetPhone(const Contact* c)
{
	if (c == NULL)
		return NULL;

	return c->phone;
}

const char* Contact_GetName(const Contact* c)
{
	if (c == NULL)
		return NULL;

	return c->name;
}

const int Contact_GetAge(const Contact* c)
{
	if (c == NULL)
		return -1;

	return c->age;
}