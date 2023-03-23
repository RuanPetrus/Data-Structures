#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CHILDREN_PER_NODE 4

typedef struct Tree Tree;

struct Tree
{
	int value;
	Tree *children[MAX_CHILDREN_PER_NODE];
};

Tree tree_init(int value)
{
	Tree tree;
	tree.value = value;
	for (int i = 0; i < MAX_CHILDREN_PER_NODE; i++) {
		tree.children[i] = NULL;
	}
	return tree;
}

Tree *tree_make(int value)
{
	Tree *tree = (Tree *) malloc(sizeof(Tree));
	tree->value = value;
	for (int i = 0; i < MAX_CHILDREN_PER_NODE; i++) {
		tree->children[i] = NULL;
	}
}

void tree_insert(Tree *parent, Tree *child, size_t position)
{
	parent->children[position] = child;
}


void _tree_traverse_print(Tree *tree, int level)
{
	if (tree == NULL)
		return;

	for (int i = 0; i < level; i++){
		printf("  ");
	}
	printf("- Node (%d):\n", tree->value);

	for (int i = 0; i < MAX_CHILDREN_PER_NODE; i++){
		_tree_traverse_print(tree->children[i], level + 1);
	}
}

void tree_traverse_print(Tree *tree)
{
	_tree_traverse_print(tree, 0);
}

void tree_traverse_free(Tree *tree)
{
	if (tree == NULL)
		return;

	for (int i = 0; i < MAX_CHILDREN_PER_NODE; i++){
		tree_traverse_free(tree->children[i]);
	}
	free(tree);
}

int main()
{
	Tree *tree = tree_make(1);

	Tree *a = tree_make(2);
	Tree *b = tree_make(3);
	Tree *c = tree_make(4);

	tree_insert(tree, a, 0);
	tree_insert(tree, b, 1);
	tree_insert(tree, c, 2);

	tree_insert(b, tree_make(4), 0);
	tree_insert(b, tree_make(5), 1);

	tree_traverse_print(tree);
	tree_traverse_free(tree);

	return 0;
}
