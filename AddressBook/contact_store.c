#include <stdio.h>
#include <stdlib.h>
#include "contact_store.h"

typedef struct _Node {
	Contact data;
	struct _Node* next;
	struct _Node* prev;
} Node;

struct _ContactStore {
	Node head;
	Node tail;
};

ContactStore* CreateContactStore(void)
{
	ContactStore* store = (ContactStore*)malloc(sizeof(ContactStore));
	if (store == NULL)
		return NULL;
	store->head.next = &store->tail;
	store->head.prev = NULL;
	store->tail.next = NULL;
	store->tail.prev = &store->head;
	return store;
}

void DestroyContactStore(ContactStore* store)
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

void PrintAllContacts(const ContactStore* store)
{
	if (store == NULL)
		return;

	Node* curr = store->head.next;
	while (curr != &store->tail)
	{
		printf("%d %s %s\n", curr->data.age, curr->data.name, curr->data.phone);
		curr = curr->next;
	}
}

int AddContactToFront(ContactStore* store, const Contact* contact)
{
	if (store == NULL || contact == NULL)
		return 0;
	
	Node* pNewNode = (Node*)malloc(sizeof(Node));
	if (pNewNode == NULL)
		return 0;
	pNewNode->data = *contact;
	pNewNode->next = store->head.next;
	pNewNode->prev = &store->head;
	store->head.next->prev = pNewNode;
	store->head.next = pNewNode;
	return 1;
}

int AddContactToEnd(ContactStore* store, const Contact* contact)
{
	if (store == NULL || contact == NULL)
		return 0;

	Node* pNewNode = (Node*)malloc(sizeof(Node));
	if (pNewNode == NULL)
		return 0;
	pNewNode->data = *contact;
	pNewNode->next = &store->tail;
	pNewNode->prev = store->tail.prev;
	store->tail.prev->next = pNewNode;
	store->tail.prev = pNewNode;
	return 1;
}