#pragma once

#include "contact.h"

typedef struct _ContactStore ContactStore;

int ContactStore_IsEmpty(const ContactStore* store);
int ContactStore_HasPhone(const ContactStore* store, const char* phone);

ContactStore* ContactStore_Create(void);
void ContactStore_Destroy(ContactStore* store);
void ContactStore_PrintAll(const ContactStore* store);
int ContactStore_AddToFront(ContactStore* store, const Contact* contact);
int ContactStore_AddToEnd(ContactStore* store, const Contact* contact);
Contact* ContactStore_Take(ContactStore* store);
int ContactStore_CombineByOp(ContactStore* resultStore, ContactStore* leftStore, ContactStore* rightStore, const char* op);