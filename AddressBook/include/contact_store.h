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
/// Inserts a Contact into the tree.
/// The tree takes ownership of the Contact and performs a deep copy.
/// The caller must not free or reuse the original Contact after insertion.
/// </summary>
int ContactStore_RBT_Insert(ContactStore_RBT* store, const Contact* data);
const Contact* ContactStore_RBT_FindByPhone(ContactStore_RBT* store, const char* phone);
int ContactStore_RBT_Iterate(const ContactStore_RBT* store, ContactCallback callback, void* userData);

/// <summary>
/// Combines two contact stores into a result store.
/// - If a contact exists in both 'leftStore' and 'rightStore', the contact from 'LeftStore is used.
/// - The result store receives a deep copy of each contact.
/// </summary>
int ContactStore_RBT_CombineByOp(ContactStore_RBT* resultStore, ContactStore_RBT* leftStore, ContactStore_RBT* rightStore, const char* op);
