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