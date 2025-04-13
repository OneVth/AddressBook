#pragma once

#include "contact.h"

typedef struct _ContactStore ContactStore;
typedef struct _ContactStore_RBT ContactStore_RBT;
typedef int (*ContactCallback)(const Contact* contact, void* userData);

int ContactStore_IsEmpty(const ContactStore* store);
int ContactStore_HasPhone(const ContactStore* store, const char* phone);

ContactStore* ContactStore_Create(void);
void ContactStore_Destroy(ContactStore* store);
void ContactStore_PrintAll(const ContactStore* store);
int ContactStore_AddToFront(ContactStore* store, const Contact* contact);
int ContactStore_AddToEnd(ContactStore* store, const Contact* contact);
const Contact* ContactStore_Take(ContactStore* store);
int ContactStore_CombineByOp(ContactStore* resultStore, ContactStore* leftStore, ContactStore* rightStore, const char* op);
int ContactStore_Iterate(const ContactStore* store, ContactCallback callback, void* userData);

// RBT
int ContactStore_RBT_IsEmpty(const ContactStore_RBT* store);
int ContactStore_RBT_HasPhone(const ContactStore_RBT* store, const char* phone);

ContactStore_RBT* ContactStore_RBT_Create(void);
void ContactStore_RBT_Destroy(ContactStore_RBT* store);

/// <summary>
/// Inserts a Contact into the tree. The tree takes ownership of the contact.
/// The caller must not free the contact after insertion.
/// </summary>
int ContactStore_RBT_Insert(ContactStore_RBT* store, const Contact* data);

