
#ifndef __HANDY_C_CONTAINER_TREE_H
#define __HANDY_C_CONTAINER_TREE_H

#include <stdbool.h>
#include <stddef.h>
#include "shared_types.h"

typedef bool __rb_tree_color_type;

typedef struct __c_tree_node {
    struct __c_tree_node* parent;
    struct __c_tree_node* left;
    struct __c_tree_node* right;
    CReferencePtr data;
    __rb_tree_color_type color;
} CTreeNode;

typedef struct __c_tree {
    CCompare key_compare;
    CTreeNode* header;
    size_t node_count;
} CTree;

/**
 * constructor/destructor
 */
CTree* CTREE_CreateTree(CTree** tree, CCompare comp);
void CTREE_DestroyTree(CTree* tree);

/**
 * iterators
 */
CTreeNode* CTREE_Begin(CTree* tree);
CTreeNode* CTREE_End(CTree* tree);
void CTREE_Forward(CTreeNode** node);
void CTREE_Backward(CTreeNode** node);

/**
 * capacity
 */
bool CTREE_Empty(CTree* tree);
size_t CTREE_Size(CTree* tree);
size_t CTREE_MaxSize(void);

/**
 * modifiers
 */
CTreeNode* CTREE_InsertEqual(CTree* tree, CReferencePtr data);
CTreeNode* CTREE_InsertUnique(CTree* tree, CReferencePtr data);
void CTREE_Erase(CTree* tree, CTreeNode* node);

/**
 * operations
 */

/**
 * algorithms
 */
CTreeNode* CTREE_Find(CTree* tree, CReferencePtr data);

#endif // __HANDY_C_CONTAINER_TREE_H
