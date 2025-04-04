#pragma once

#include "contact.h"

typedef struct _ContactStore ContactStore;

ContactStore* CreateContactStore(void);
void DestroyContactStore(ContactStore* store);
void PrintAllContacts(const ContactStore* store);
int AddContactToFront(ContactStore* store, const Contact* contact);
int AddContactToEnd(ContactStore* store, const Contact* contact);