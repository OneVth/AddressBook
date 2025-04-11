#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact_store.h"

typedef enum { RED, BLACK } COLOR;

typedef struct _Node {
	const Contact* data;
	struct _Node* next;
	struct _Node* prev;
} Node;

typedef struct _RBNode {
	const Contact* data;
	COLOR color;
	struct _RBNode* parent;
	struct _RBNode* left;
	struct _RBNode* right;
} RBNode;

struct _ContactStore {
	Node head;
	Node tail;
};

struct _ContactStore_RBT {
	RBNode* root;
	RBNode* nil;
};

int ContactStore_IsEmpty(const ContactStore* store)
{
	if (store == NULL)
		return -1;
	return store->head.next == &store->tail;
}

int ContactStore_HasPhone(const ContactStore* store, const char* phone)
{
	if (store == NULL || phone == NULL)
		return -1;

	Node* curr = store->head.next;
	while (curr != &store->tail)
	{
		if (strcmp(Contact_GetPhone(curr->data), phone) == 0)
			return 1;
		curr = curr->next;
	}
	return 0;
}

ContactStore* ContactStore_Create(void)
{
	ContactStore* pStore = (ContactStore*)malloc(sizeof(ContactStore));
	if (pStore == NULL)
		return NULL;
	pStore->head.next = &pStore->tail;
	pStore->head.prev = NULL;
	pStore->tail.next = NULL;
	pStore->tail.prev = &pStore->head;
	return pStore;
}

void ContactStore_Destroy(ContactStore* store)
{
	if (store == NULL)
		return;
	Node* curr = store->head.next;
	while (curr != &store->tail)
	{
		Node* del = curr;
		curr = curr->next;
		if(del->data != NULL)
			Contact_Destroy(del->data);
		free(del);
	}
	free(store);
}

void ContactStore_PrintAll(const ContactStore* store)
{
	if (store == NULL)
		return;

	Node* curr = store->head.next;
	while (curr != &store->tail)
	{
		printf("%d %s %s\n", 
			Contact_GetAge(curr->data), 
			Contact_GetName(curr->data), 
			Contact_GetPhone(curr->data)
		);
		curr = curr->next;
	}
}

int ContactStore_AddToFront(ContactStore* store, const Contact* contact)
{
	if (store == NULL || contact == NULL)
		return 0;
	
	Node* pNewNode = (Node*)malloc(sizeof(Node));
	if (pNewNode == NULL)
		return 0;
	
	pNewNode->data = Contact_Create(
		Contact_GetAge(contact),
		Contact_GetName(contact),
		Contact_GetPhone(contact)
	);

	pNewNode->next = store->head.next;
	pNewNode->prev = &store->head;
	store->head.next->prev = pNewNode;
	store->head.next = pNewNode;
	return 1;
}

int ContactStore_AddToEnd(ContactStore* store, const Contact* contact)
{
	if (store == NULL || contact == NULL)
		return 0;

	Node* pNewNode = (Node*)malloc(sizeof(Node));
	if (pNewNode == NULL)
		return 0;
	
	pNewNode->data = Contact_Create(
		Contact_GetAge(contact),
		Contact_GetName(contact),
		Contact_GetPhone(contact)
	);

	pNewNode->next = &store->tail;
	pNewNode->prev = store->tail.prev;
	store->tail.prev->next = pNewNode;
	store->tail.prev = pNewNode;
	return 1;
}

const Contact* ContactStore_Take(ContactStore* store)
{
	if (store == NULL || ContactStore_IsEmpty(store))
		return NULL;

	Node* ptr = store->head.next;
	const Contact* pContact = ptr->data;
	ptr->prev->next = ptr->next;
	ptr->next->prev = ptr->prev;

	free(ptr);
	return pContact;
}

int ContactStore_CombineByOp(ContactStore* resultStore, ContactStore* leftStore, ContactStore* rightStore, const char* op)
{
	Node* leftCurr = leftStore->head.next;
	Node* rightCurr = rightStore->head.next;

	if (strcmp(op, "OR") == 0 || strcmp(op, "or") == 0)
	{
		while (leftCurr != &leftStore->tail)
		{
			ContactStore_AddToEnd(resultStore, leftCurr->data);
			leftCurr = leftCurr->next;
		}

		while (rightCurr != &rightStore->tail)
		{
			if (ContactStore_HasPhone(resultStore, 
				Contact_GetPhone(rightCurr->data)) == 0)
			{
				ContactStore_AddToEnd(resultStore, rightCurr->data);
			}
			rightCurr = rightCurr->next;
		}
	}
	else if (strcmp(op, "AND") == 0 || strcmp(op, "and") == 0)
	{
		while (leftCurr != &leftStore->tail)
		{
			if (ContactStore_HasPhone(rightStore, 
				Contact_GetPhone(leftCurr->data)) == 1)
			{
				ContactStore_AddToEnd(resultStore, leftCurr->data);
			}
			leftCurr = leftCurr->next;
		}
	}
	else
	{
		return 0;
	}

	return 1;
}

int ContactStore_Iterate(const ContactStore* store, ContactCallback callback, void* userData)
{
	if (store == NULL || callback == NULL)
		return 0;

	Node* curr = store->head.next;
	while (curr != &store->tail)
	{
		if (!callback(curr->data, userData))
			break;
		curr = curr->next;
	}

	return 1;
}

// RBT
int ContactStore_RBT_IsEmpty(const ContactStore_RBT* store)
{
	return 0;
}

int ContactStore__RBT_HasPhone(const ContactStore_RBT* store, const char* phone)
{
	return 0;
}

ContactStore_RBT* ContactStore_RBT_Create(void)
{
	return NULL;
}

void ContactStore_RBT_Destroy(ContactStore_RBT* store)
{
	return;
}

int ContactStore_RBT_Insert(ContactStore_RBT* store, const Contact* data)
{
	return 0;
}