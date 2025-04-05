#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact_store.h"

typedef struct _Node {
	const Contact* data;
	struct _Node* next;
	struct _Node* prev;
} Node;

struct _ContactStore {
	Node head;
	Node tail;
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