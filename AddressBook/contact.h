#pragma once

#define MAX_NAME_LEN 32
#define MAX_PHONE_LEN 14	// 000-0000-0000 + '\0'
#define MAXAGE 120

typedef struct _Contact Contact;

Contact* Contact_Create(int age, const char* name, const char* phone);
void Contact_Destroy(const Contact* c);
const char* Contact_GetPhone(const Contact* c);
const char* Contact_GetName(const Contact* c);
const int Contact_GetAge(const Contact* c);
size_t Contact_GetSize(void);
int Contact_SetAge(Contact* c, const int age);