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

typedef struct {
	ContactStore_RBT* result;
	const ContactStore_RBT* right;
} CombineContext;

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
	if (store == NULL) return 0;
	if (store->root == store->nil)
		return 1;

	return 0;
}

int ContactStore_RBT_HasPhone(const ContactStore_RBT* store, const char* phone)
{
	if (store == NULL || phone == NULL)
		return 0;

	RBNode* cur = store->root;

	while (cur != store->nil)
	{
		int cmp = strcmp(Contact_GetPhone(cur->data), phone);
		if (cmp == 0)
			return 1;

		if (cmp < 0)
			cur = cur->right;
		else
			cur = cur->left;
	}
	return 0;
}

ContactStore_RBT* ContactStore_RBT_Create(void)
{
	ContactStore_RBT* pStore = malloc(sizeof(ContactStore_RBT));
	if (pStore == NULL) return NULL;

	// sentinel node
	pStore->nil = malloc(sizeof(RBNode));
	if (pStore->nil == NULL)
	{
		free(pStore);
		return NULL;
	}

	pStore->nil->color = BLACK;
	pStore->nil->data = NULL;
	pStore->nil->left = pStore->nil;
	pStore->nil->right = pStore->nil;
	pStore->nil->parent = pStore->nil;

	pStore->root = pStore->nil;

	return pStore;
}

static void FreeRBTree(ContactStore_RBT* store, RBNode* node)
{
	if (node == store->nil) return;

	FreeRBTree(store, node->left);
	FreeRBTree(store, node->right);

	free((void*)node->data);
	free(node);
	return;
}

void ContactStore_RBT_Destroy(ContactStore_RBT* store)
{
	if (store == NULL) return;

	FreeRBTree(store, store->root);

	free(store->nil);
	free(store);
	return;
}

static void RotateLeft(ContactStore_RBT* store, RBNode* x)
{
	RBNode* y = x->right;
	x->right = y->left;

	if (y->left != store->nil)
		y->left->parent = x;

	y->parent = x->parent;

	if (x->parent == store->nil)
		store->root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
	return;
}

static void RotateRight(ContactStore_RBT* store, RBNode* y)
{
	RBNode* x = y->left;
	y->left = x->right;

	if (x->left != store->nil)
		x->right->parent = y;

	x->parent = y->parent;

	if (y->parent == store->nil)
		store->root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	x->right = y;
	y->parent = x;
	return;
}

static void InsertFixUp(ContactStore_RBT* store, RBNode* z)
{
	while (z->parent->color == RED)
	{
		if (z->parent == z->parent->parent->left)
		{
			RBNode* y = z->parent->parent->right;	// Uncle

			// Case 1: Uncle is RED
			if (y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				// Case 2: Left-Right
				if (z == z->parent->right)
				{
					z = z->parent;
					RotateLeft(store, z);
				}

				// Case 3: Left-Left
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				RotateRight(store, z->parent->parent);
			}
		}
		else // z->parent == z->parent->parent->right (mirror case)
		{
			RBNode* y = z->parent->parent->left;	// Uncle

			// Case 1 (mirror)
			if (y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				// Case 2 (mirror)
				if (z == z->parent->left)
				{
					z = z->parent;
					RotateRight(store, z);
				}

				// Case 3 (mirror)
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				RotateLeft(store, z->parent->parent);
			}
		}
	}

	store->root->color = BLACK;
}

int ContactStore_RBT_Insert(ContactStore_RBT* store, const Contact* data)
{
	RBNode* y = store->nil;
	RBNode* x = store->root;
	RBNode* z = malloc(sizeof(RBNode));
	if (z == NULL) return 0;

	z->data = Contact_Create(
		Contact_GetAge(data), 
		Contact_GetName(data), 
		Contact_GetPhone(data)
	);
	z->color = RED;
	z->left = z->right = z->parent = store->nil;

	while (x != store->nil)
	{
		y = x;
		if (strcmp(Contact_GetPhone(data), Contact_GetPhone(x->data)) < 0)
			x = x->left;
		else
			x = x->right;
	}

	z->parent = y;
	if (y == store->nil)
		store->root = z;
	else if (strcmp(Contact_GetPhone(data), Contact_GetPhone(y->data)) < 0)
		y->left = z;
	else
		y->right = z;

	InsertFixUp(store, z);
	return 1;
}

static int RBT_InOrderTraverse(RBNode* node, RBNode* nil, ContactCallback callback, void* userData)
{
	if (node == nil) return 1;

	if (!RBT_InOrderTraverse(node->left, nil, callback, userData))
		return 0;

	if (!callback(node->data, userData))
		return 0;

	if (!RBT_InOrderTraverse(node->right, nil, callback, userData))
		return 0;

	return 1;
}

int ContactStore_RBT_Iterate(const ContactStore_RBT* store, ContactCallback callback, void* userData)
{
	if (store == NULL || callback == NULL) return 0;

	return RBT_InOrderTraverse(store->root, store->nil, callback, userData);
}

static int InsertAllCallback(const Contact* contact, void* userData)
{
	ContactStore_RBT* pResultStore = (ContactStore_RBT*)userData;
	ContactStore_RBT_Insert(pResultStore, contact);
	return 1;
}

static int InsertIfAbsentCallback(const Contact* contact, void* userData)
{
	ContactStore_RBT* pResultStore = (ContactStore_RBT*)userData;
	if (!ContactStore_RBT_HasPhone(pResultStore, Contact_GetPhone(contact)))
		ContactStore_RBT_Insert(pResultStore, contact);
	return 1;
}

static int InsertIfPresentInRightCallback(const Contact* contact, void* userData)
{
	CombineContext* pCombineContext = (CombineContext*)userData;
	ContactStore_RBT* pResultStore = pCombineContext->result;
	const ContactStore_RBT* pRightStore = pCombineContext->right;
	if (ContactStore_RBT_HasPhone(pRightStore, Contact_GetPhone(contact)))
		ContactStore_RBT_Insert(pResultStore, contact);
	return 1;
}

int ContactStore_RBT_CombineByOp(ContactStore_RBT* resultStore, ContactStore_RBT* leftStore, ContactStore_RBT* rightStore, const char* op)
{
	if (op == NULL || resultStore == NULL || leftStore == NULL || rightStore == NULL)
		return 0;

	if (strcmp(op, "OR") == 0 || strcmp(op, "or") == 0)
	{
		ContactStore_RBT_Iterate(leftStore, InsertAllCallback, resultStore);
		ContactStore_RBT_Iterate(rightStore, InsertIfAbsentCallback, resultStore);
	}
	else if (strcmp(op, "AND") == 0 || strcmp(op, "and") == 0)
	{
		CombineContext combineContext = { resultStore, rightStore };
		ContactStore_RBT_Iterate(leftStore, InsertIfPresentInRightCallback, &combineContext);
	}
	else
	{
		return 0;
	}
	return 1;
}
