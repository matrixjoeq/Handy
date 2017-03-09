
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "tree.h"

static const rb_tree_color_type s_rb_tree_color_red = false;
static const rb_tree_color_type s_rb_tree_color_black = true;

STATIC bool isRootNode(CTreeNode* node)
{
    if (!node) {
        return false;
    }

    return (node->parent->parent == node &&
            node->left != node &&
            node->right != node);
}

STATIC bool isLeftNode(CTreeNode* node)
{
    if (!node) {
        return false;
    }

    return (node->parent->left == node);
}

STATIC bool isRightNode(CTreeNode* node)
{
    if (!node) {
        return false;
    }

    return (node->parent->right == node);
}

STATIC CTreeNode* minimum(CTreeNode* node)
{
	if (!node) {
		return NULL;
	}
	
	while (node->left) {
		node = node->left;
	}
	
	return node;
}

STATIC CTreeNode* maximum(CTreeNode* node)
{
	if (!node) {
		return NULL;
	}
	
	while (node->right) {
		node = node->right;
	}
	
	return node;
}

STATIC void clockwiseSingleRotate(CTreeNode* node)
{
    if (!node || !node->left) {
        return;
    }

    CTreeNode* x = node;
    CTreeNode* y = x->left;

	x->left = y->right;
    if (y->right) {
        y->right->parent = x;
    }

    if (isRootNode(x)) {
        x->parent->parent = y;
    }
    else if (isLeftNode(x)) {
        x->parent->left = y;
    }
    else if (isRightNode(x)) {
        x->parent->right = y;
    }

    y->parent = x->parent;
    y->right = x;
    x->parent = y;
}

STATIC void counterclockwiseSingleRotate(CTreeNode* node)
{
    if (!node || !node->right) {
        return;
    }

    CTreeNode* x = node;
    CTreeNode* y = x->right;

	x->right = y->left;
    if (y->left) {
        y->left->parent = x;
    }

    if (isRootNode(x)) {
        x->parent->parent = y;
    }
    else if (isLeftNode(x)) {
        x->parent->left = y;
    }
    else if (isRightNode(x)) {
        x->parent->right = y;
    }

    y->parent = x->parent;
    y->left = x;
    x->parent = y;
}

STATIC void clockwiseDoubleRotate(CTreeNode* node)
{
    if (!node || !node->left) {
        return;
    }

    counterclockwiseSingleRotate(node->left);
    clockwiseSingleRotate(node);
}

STATIC void counterclockwiseDoubleRotate(CTreeNode* node)
{
    if (!node || !node->right) {
        return;
    }

    clockwiseSingleRotate(node->right);
    counterclockwiseSingleRotate(node);
}

STATIC bool defaultKeyCompare(CReferencePtr lhs, CReferencePtr rhs)
{
    return (lhs < rhs);
}

STATIC CTreeNode* createNode(CTreeNode** node)
{
    if (!node || *node) {
        return NULL;
    }

    *node = (CTreeNode*) malloc(sizeof(CTreeNode));
    if (!(*node)) {
        return NULL;
    }

    (*node)->parent = NULL;
    (*node)->left   = NULL;
    (*node)->right  = NULL;
    (*node)->data   = NULL;
    (*node)->color  = s_rb_tree_color_red;

    return *node;
}

CTree* CTREE_CreateTree(CTree** tree, CCompare comp)
{
    if (!tree || *tree) {
        return NULL;
    }

    *tree = (CTree*) malloc(sizeof(CTree));
    if (!(*tree)) {
        return NULL;
    }

    (*tree)->header = NULL;
    if (!createNode(&((*tree)->header))) {
        FREE(*tree);
        return NULL;
    }

    (*tree)->key_compare = comp ? comp : defaultKeyCompare;
    (*tree)->header->left = (*tree)->header;
    (*tree)->header->right = (*tree)->header;

    return *tree;
}

void CTREE_DestroyTree(CTree* tree)
{
}
