// for unit test only
#pragma once

#include "contact_store.h"

typedef enum {RED, BLACK} COLOR;

typedef struct _RBNode {
	const Contact* data;
	COLOR color;
	struct _RBNode* parent;
	struct _RBNode* left;
	struct _RBNode* right;
} RBNode;

struct _ContactStore_RBT {
	RBNode* root;
	RBNode* nil;
};