#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact_store.h"
#include "common.h"

typedef enum { RED, BLACK } COLOR;

typedef struct _RBNode {
	const Contact* data;
	COLOR color;
	struct _RBNode* parent;
	struct _RBNode* left;
	struct _RBNode* right;
} RBNode;

struct _ContactStore {
	RBNode* root;
	RBNode* nil;
};

typedef struct {
	ContactStore* result;
	const ContactStore* right;
} CombineContext;

int ContactStore_IsEmpty(const ContactStore* store)
{
	if (store == NULL) return 0;
	if (store->root == store->nil)
		return 1;

	return 0;
}

int ContactStore_HasPhone(const ContactStore* store, const char* phone)
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

ContactStore* ContactStore_Create(void)
{
	ContactStore* pStore = malloc(sizeof(ContactStore));
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

static void FreeRBTree(ContactStore* store, RBNode* node)
{
	if (node == store->nil) return;

	FreeRBTree(store, node->left);
	FreeRBTree(store, node->right);

	free((void*)node->data);
	free(node);
	return;
}

void ContactStore_Destroy(ContactStore* store)
{
	if (store == NULL) return;

	FreeRBTree(store, store->root);

	free(store->nil);
	free(store);
	return;
}

static void RotateLeft(ContactStore* store, RBNode* x)
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

static void RotateRight(ContactStore* store, RBNode* y)
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

static void InsertFixUp(ContactStore* store, RBNode* z)
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

int ContactStore_Insert(ContactStore* store, const Contact* data)
{
	if (store == NULL || data == NULL)
		return 0;

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

const Contact* ContactStore_FindByPhone(ContactStore* store, const char* phone)
{
	if (store == NULL || phone == NULL)
		return NULL;

	if (!Str_IsPhoneFormat(phone))
		return NULL;

	RBNode* current = store->root;
	while (current != store->nil)
	{
		int cmp = strcmp(phone, Contact_GetPhone(current->data));
		if (cmp == 0)
			return current->data;
		else if (cmp < 0)
			current = current->left;
		else
			current = current->right;
	}
	return NULL;
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

int ContactStore_Iterate(const ContactStore* store, ContactCallback callback, void* userData)
{
	if (store == NULL || callback == NULL) return 0;

	return RBT_InOrderTraverse(store->root, store->nil, callback, userData);
}

static int InsertAllCallback(const Contact* contact, void* userData)
{
	ContactStore* pResultStore = (ContactStore*)userData;
	ContactStore_Insert(pResultStore, contact);
	return 1;
}

static int InsertIfAbsentCallback(const Contact* contact, void* userData)
{
	ContactStore* pResultStore = (ContactStore*)userData;
	if (!ContactStore_HasPhone(pResultStore, Contact_GetPhone(contact)))
		ContactStore_Insert(pResultStore, contact);
	return 1;
}

static int InsertIfPresentInRightCallback(const Contact* contact, void* userData)
{
	CombineContext* pCombineContext = (CombineContext*)userData;
	ContactStore* pResultStore = pCombineContext->result;
	const ContactStore* pRightStore = pCombineContext->right;
	if (ContactStore_HasPhone(pRightStore, Contact_GetPhone(contact)))
		ContactStore_Insert(pResultStore, contact);
	return 1;
}

int ContactStore_CombineByOp(ContactStore* resultStore, ContactStore* leftStore, ContactStore* rightStore, const char* op)
{
	if (op == NULL || resultStore == NULL || leftStore == NULL || rightStore == NULL)
		return 0;

	if (strcmp(op, "OR") == 0 || strcmp(op, "or") == 0)
	{
		ContactStore_Iterate(leftStore, InsertAllCallback, resultStore);
		ContactStore_Iterate(rightStore, InsertIfAbsentCallback, resultStore);
	}
	else if (strcmp(op, "AND") == 0 || strcmp(op, "and") == 0)
	{
		CombineContext combineContext = { resultStore, rightStore };
		ContactStore_Iterate(leftStore, InsertIfPresentInRightCallback, &combineContext);
	}
	else
	{
		return 0;
	}
	return 1;
}

ContactStore* ContactStore_Clone(ContactStore* source)
{
	ContactStore* clone = ContactStore_Create();
	if (clone == NULL)
		return NULL;

	ContactStore_Iterate(source, InsertAllCallback, clone);
	return clone;
}