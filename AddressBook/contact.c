#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "contact.h"

struct _Contact {
	int age;
	char name[MAX_NAME_LEN];
	char phone[MAX_PHONE_LEN];
};

Contact* Contact_Create(int age, const char* name, const char* phone)
{
	if (age < 0 || age > MAXAGE)
		return NULL;

	if (name == NULL || !Str_IsAllAlpha(name))
		return NULL;

	if (phone == NULL || !Str_IsPhoneFormat(phone))
		return NULL;

	Contact* pContact = (Contact*)malloc(sizeof(Contact));
	if (pContact == NULL)
		return NULL;

	pContact->age = age;
	strcpy_s(pContact->name, sizeof(pContact->name), name);
	strcpy_s(pContact->phone, sizeof(pContact->phone), phone);

	return pContact;
}

void Contact_Destroy(const Contact* c)
{
	if (c == NULL)
		return;

	free((void*)c);
	c = NULL;
	return;
}

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

size_t Contact_GetSize(void)
{
	return sizeof(Contact);
}

int Contact_SetAge(Contact* c, const int age)
{
	if (c == NULL || age < 0 || age > MAXAGE)
		return 0;

	c->age = age;
	return 1;
}

int Contact_SetName(Contact* c, const char* name)
{
	if (c == NULL || name == NULL || !Str_IsAllAlpha(name))
		return 0;

	strcpy_s(c->name, sizeof(c->name), name);
	return 1;
}