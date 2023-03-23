#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "stdbool.h"

typedef struct Bt Bt;

struct Bt
{
	int value;
	Bt* left;
	Bt* right;
};


Bt bt_init(int value)
{
	Bt bt;
	bt.value = value;
	bt.left = NULL;
	bt.right = NULL;
	return bt;
}

Bt *bt_make(int value)
{
	Bt *bt = (Bt *) malloc(sizeof(Bt));
	bt->value = value;
	bt->left = NULL;
	bt->right = NULL;

	return bt;
}

void bt_insert(Bt *parent, Bt *child)
{
	if (parent == NULL)
		return;

	if (child->value < parent->value) {
		if (parent->left != NULL){
			bt_insert(parent->left, child);
		}
		else {
			parent->left = child;
		}
		return;
	 }

	if (parent->right != NULL){
		bt_insert(parent->right, child);
	}
	else {
		parent->right = child;
	}
	return;
}

void bt_traverse_print(Bt *bt, int level)
{
	if (bt == NULL)
		return;

	for (int i = 0; i < level; i++){
		printf("  ");
	}
	printf("- Node (%d):\n", bt->value);

	bt_traverse_print(bt->left, level + 1);
	bt_traverse_print(bt->right, level + 1);
}

void bt_traverse_free(Bt *bt)
{
	if (bt == NULL)
		return;


	bt_traverse_free(bt->left);
	bt_traverse_free(bt->right);
	free(bt);
}

bool bt_contains(Bt *bt, int n)
{
	if (bt == NULL)
		return false;

	if (bt->value == n)
		return true;
	
	if (n < bt->value)
		return bt_contains(bt->left, n);

	return bt_contains(bt->right, n);
}

int main()
{
	Bt *bt = bt_make(0);
	bt_insert(bt, bt_make(2));
	bt_insert(bt, bt_make(3));
	bt_insert(bt, bt_make(4));
	bt_insert(bt, bt_make(1));
	bt_insert(bt, bt_make(-1));
	bt_insert(bt, bt_make(-5));

	bt_traverse_print(bt, 0);

	assert(bt_contains(bt, 0));
	assert(bt_contains(bt, 4));
	assert(bt_contains(bt, -5));
	assert(!bt_contains(bt, -2));
	assert(!bt_contains(bt, 5));

	bt_traverse_free(bt);
	return 0;
}
