#pragma once

#include "contact.h"

typedef struct _ContactStore ContactStore;
typedef int (*ContactCallback)(const Contact* contact, void* userData);

// RBT
int ContactStore_IsEmpty(const ContactStore* store);
int ContactStore_HasPhone(const ContactStore* store, const char* phone);

ContactStore* ContactStore_Create(void);
void ContactStore_Destroy(ContactStore* store);

/// <summary>
/// Inserts a Contact into the tree.
/// The tree takes ownership of the Contact and performs a deep copy.
/// The caller must not free or reuse the original Contact after insertion.
/// </summary>
int ContactStore_Insert(ContactStore* store, const Contact* data);

/// <summary>
/// Searches the tree for a contact with the given phone number.
/// The returned pointer is owned by the tree and must NOT be freed by the caller.
/// </summary>
const Contact* ContactStore_FindByPhone(ContactStore* store, const char* phone);
int ContactStore_Iterate(const ContactStore* store, ContactCallback callback, void* userData);

/// <summary>
/// Combines two contact stores into a result store.
/// - If a contact exists in both 'leftStore' and 'rightStore', the contact from 'LeftStore is used.
/// - The result store receives a deep copy of each contact.
/// </summary>
int ContactStore_CombineByOp(ContactStore* resultStore, ContactStore* leftStore, ContactStore* rightStore, const char* op);
