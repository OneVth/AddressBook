#pragma once

#define MAX_NAME_LEN 32
#define MAX_PHONE_LEN 14	// 000-0000-0000 + '\0'
#define MAXAGE 120

typedef struct _Contact Contact;

const char* Contact_GetPhone(const Contact* c);
const char* Contact_GetName(const Contact* c);
const int Contact_GetAge(const Contact* c);
Contact* Contact_Create(int age, const char* name, const char* phone);
void Contact_Destroy(Contact* c);