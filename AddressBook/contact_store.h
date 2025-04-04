#pragma once

#include "contact.h"

typedef struct _ContactStore ContactStore;

ContactStore* ContactStore_Create(void);
void ContactStore_Destroy(ContactStore* store);
void ContactStore_PrintAll(const ContactStore* store);
int ContactStore_AddToFront(ContactStore* store, const Contact* contact);
int ContactStore_AddToEnd(ContactStore* store, const Contact* contact);
