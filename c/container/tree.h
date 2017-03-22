
#ifndef __HANDY_C_CONTAINER_TREE_H
#define __HANDY_C_CONTAINER_TREE_H

#include <stdbool.h>
#include <stddef.h>
#include "shared_types.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct __c_tree_node;
typedef struct __c_tree_node CTreeNode;

struct __c_tree;
typedef struct __c_tree CTree;

/**
 * constructor/destructor
 */
CTree* CTREE_CreateTree(CTree** tree, CCompare comp);
void CTREE_DestroyTree(CTree* tree);

/**
 * element access
 */
CReferencePtr CTREE_Reference(CTreeNode* node);

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
void CTREE_Clear(CTree* tree);

/**
 * operations
 */

/**
 * algorithms
 */
CTreeNode* CTREE_Find(CTree* tree, CReferencePtr data);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __HANDY_C_CONTAINER_TREE_H
