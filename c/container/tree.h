
#ifndef __HANDY_C_CONTAINER_TREE_H
#define __HANDY_C_CONTAINER_TREE_H

#include <stdbool.h>
#include <stddef.h>
#include "shared_types.h"

typedef bool rb_tree_color_type;

typedef struct __c_tree_node {
    struct __c_tree_node* parent;
    struct __c_tree_node* left;
    struct __c_tree_node* right;
    CReferencePtr data;
    rb_tree_color_type color;
} CTreeNode;

typedef struct __c_tree {
    CCompare key_compare;
    CTreeNode* header;
} CTree;

/**
 * constructor/destructor
 */
CTree* CTREE_CreateTree(CTree** tree, CCompare comp);
void CTREE_DestroyTree(CTree* tree);


#endif // __HANDY_C_CONTAINER_TREE_H
