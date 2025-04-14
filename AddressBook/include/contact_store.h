#pragma once

#include "contact.h"

typedef struct _ContactStore_RBT ContactStore_RBT;
typedef int (*ContactCallback)(const Contact* contact, void* userData);

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

/// <summary>
/// Searches the tree for a contact with the given phone number.
/// The returned pointer is owned by the tree and must NOT be freed by the caller.
/// </summary>
const Contact* ContactStore_RBT_FindByPhone(ContactStore_RBT* store, const char* phone);
int ContactStore_RBT_Iterate(const ContactStore_RBT* store, ContactCallback callback, void* userData);

/// <summary>
/// Combines two contact stores into a result store.
/// - If a contact exists in both 'leftStore' and 'rightStore', the contact from 'LeftStore is used.
/// - The result store receives a deep copy of each contact.
/// </summary>
int ContactStore_RBT_CombineByOp(ContactStore_RBT* resultStore, ContactStore_RBT* leftStore, ContactStore_RBT* rightStore, const char* op);
