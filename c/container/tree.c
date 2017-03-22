
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "tree.h"

typedef bool __rb_tree_color_type;

struct __c_tree_node {
    struct __c_tree_node* parent;
    struct __c_tree_node* left;
    struct __c_tree_node* right;
    CReferencePtr data;
    __rb_tree_color_type color;
};

struct __c_tree {
    CCompare key_compare;
    CTreeNode* header;
    size_t node_count;
};

static const __rb_tree_color_type s_rb_tree_color_red = false;
static const __rb_tree_color_type s_rb_tree_color_black = true;

STATIC INLINE bool __is_header(CTreeNode* node)
{
    return (node ? (node->parent->parent == node &&
                    node->color == s_rb_tree_color_red) : false);
}

STATIC INLINE bool __is_root(CTreeNode* node)
{
    return (node ? (node->parent->parent == node &&
                    node->color == s_rb_tree_color_black) : false);
}

STATIC INLINE bool __is_left(CTreeNode* node)
{
    return (node ? node->parent->left == node : false);
}

STATIC INLINE bool __is_right(CTreeNode* node)
{
    return (node ? node->parent->right == node : false);
}

STATIC INLINE bool __is_black(CTreeNode* node)
{
    return (node ? (node->color == s_rb_tree_color_black) : true);
}

STATIC INLINE bool __is_red(CTreeNode* node)
{
    return (node ? (node->color == s_rb_tree_color_red) : false);
}

STATIC INLINE bool __has_left(CTreeNode* node)
{
    return (node ? node->left != NULL : false);
}

STATIC INLINE bool __has_right(CTreeNode* node)
{
    return (node ? node->right != NULL : false);
}

STATIC INLINE CTreeNode* __left(CTreeNode* node)
{
    return node->left;
}

STATIC INLINE CTreeNode* __right(CTreeNode* node)
{
    return node->right;
}

STATIC INLINE CTreeNode* __parent(CTreeNode* node)
{
    return node->parent;
}

STATIC INLINE CTreeNode* __grand_parent(CTreeNode* node)
{
    return node->parent->parent;
}

STATIC INLINE CTreeNode* __uncle(CTreeNode* node)
{
    return (__is_left(__parent(node)) ? __right(__grand_parent(node))
                                      : __left(__grand_parent(node)));
}

STATIC INLINE __rb_tree_color_type __color(CTreeNode* node)
{
    return node->color;
}

STATIC INLINE CReferencePtr __value(CTreeNode* node)
{
    return node->data;
}

STATIC INLINE CTreeNode* __root(CTree* tree)
{
    return tree->header->parent;
}

STATIC INLINE CTreeNode* __leftmost(CTree* tree)
{
    return tree->header->left;
}

STATIC INLINE CTreeNode* __rightmost(CTree* tree)
{
    return tree->header->right;
}

STATIC INLINE void __set_root(CTree* tree, CTreeNode* root)
{
    tree->header->parent = root;
}

STATIC INLINE void __set_leftmost(CTree* tree, CTreeNode* leftmost)
{
    tree->header->left = leftmost;
}

STATIC INLINE void __set_rightmost(CTree* tree, CTreeNode* rightmost)
{
    tree->header->right = rightmost;
}

STATIC CTreeNode* __minimum(CTreeNode* node)
{
    if (!node) {
        return NULL;
    }

    while (node->left) {
        node = node->left;
    }

    return node;
}

STATIC CTreeNode* __maximum(CTreeNode* node)
{
    if (!node) {
        return NULL;
    }

    while (node->right) {
        node = node->right;
    }

    return node;
}
#if 0
STATIC void __rotate_right(CTreeNode* node, CTreeNode* root)
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

    if (x == root) {
        x->parent->parent = y;
    }
    else if (__is_left(x)) {
        x->parent->left = y;
    }
    else if (__is_right(x)) {
        x->parent->right = y;
    }

    y->parent = x->parent;
    y->right = x;
    x->parent = y;
}

STATIC void __rotate_left(CTreeNode* node, CTreeNode* root)
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

    if (x == root) {
        x->parent->parent = y;
    }
    else if (__is_left(x)) {
        x->parent->left = y;
    }
    else if (__is_right(x)) {
        x->parent->right = y;
    }

    y->parent = x->parent;
    y->left = x;
    x->parent = y;
}
#endif
STATIC bool __key_compare(CReferencePtr lhs, CReferencePtr rhs)
{
    return (lhs < rhs);
}

STATIC CTreeNode* __create_node(CTreeNode** node, CReferencePtr data)
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
    (*node)->data   = data;
    (*node)->color  = s_rb_tree_color_red;

    return *node;
}

STATIC void __destroy_node(CTreeNode* node)
{
    FREE(node->data);
    FREE(node);
}

STATIC void __erase(CTreeNode* node) // erase node and it's children
{
    while (node) {
        __erase(node->right);
        CTreeNode* left = node->left;
        __destroy_node(node);
        node = left;
    }
}
#if 0
STATIC void __rebalance_insert(CTree* tree, CTreeNode* node)
{
    if (!tree || !node) {
        return;
    }

    while (__root(tree) != node && __is_red(__parent(node))) {
        if (__is_left(__parent(node))) {
            if (__is_red(__uncle(node))) {
                __parent(node)->color = s_rb_tree_color_black;
                __uncle(node)->color = s_rb_tree_color_black;
                __grand_parent(node)->color = s_rb_tree_color_red;
                node = __grand_parent(node);
            }
            else {
                if (__is_right(node)) {
                    node = __parent(node);
                    __rotate_left(node, __root(tree));
                }

                __parent(node)->color = s_rb_tree_color_black;
                __grand_parent(node)->color = s_rb_tree_color_red;
                __rotate_right(__grand_parent(node), __root(tree));
            }
        }
        else {
            if (__is_red(__uncle(node))) {
                __parent(node)->color = s_rb_tree_color_black;
                __uncle(node)->color = s_rb_tree_color_black;
                __grand_parent(node)->color = s_rb_tree_color_red;
                node = __grand_parent(node);
            }
            else {
                if (__is_left(node)) {
                    node = __parent(node);
                    __rotate_right(node, __root(tree));
                }

                __parent(node)->color = s_rb_tree_color_black;
                __grand_parent(node)->color = s_rb_tree_color_red;
                __rotate_left(__grand_parent(node), __root(tree));
            }
        }
    }

    __root(tree)->color = s_rb_tree_color_black;
}
#endif
STATIC CTreeNode* __insert(CTree* tree, CTreeNode* parent, CReferencePtr data)
{
    CTreeNode* node = NULL;
    if (!__create_node(&node, data)) {
        return NULL;
    }

    CCompare key_compare = tree->key_compare;
    CTreeNode* header = tree->header;
    if (parent == tree->header || key_compare(data, parent->data)) {
        parent->left = node;

        if (parent == header) {
            header->parent = node;
            header->right = node;
        }
        else if (parent == __leftmost(tree)) {
            header->left = node;
        }
    }
    else {
        parent->right = node;

        if (parent == __rightmost(tree)) {
            header->right = node;
        }
    }

    node->parent = parent;

    //__rebalance_insert(tree, node);
    ++(tree->node_count);

    return node;
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
    if (!__create_node(&((*tree)->header), NULL)) {
        FREE(*tree);
        return NULL;
    }

    (*tree)->node_count = 0;
    (*tree)->key_compare = comp ? comp : __key_compare;
    (*tree)->header->left = (*tree)->header;
    (*tree)->header->right = (*tree)->header;

    return *tree;
}

void CTREE_DestroyTree(CTree* tree)
{
    CTREE_Clear(tree);
    FREE(tree);
}

CReferencePtr CTREE_Reference(CTreeNode* node)
{
    return node ? __value(node) : NULL;
}

CTreeNode* CTREE_Begin(CTree* tree)
{
    return tree ? __leftmost(tree) : NULL;
}

CTreeNode* CTREE_End(CTree* tree)
{
    return tree ? tree->header : NULL;
}

void CTREE_Forward(CTreeNode** node)
{
    if (!node || !(*node)) {
        return;
    }

    if ((*node)->right) {
        *node = __minimum((*node)->right);
    }
    else {
        CTreeNode* parent = (*node)->parent;
        while (parent->right == *node) {
            *node = parent;
            parent = parent->parent;
        }

        // in the case of node is header and parent is root
        if (parent != (*node)->right) {
            *node = parent;
        }
    }
}

void CTREE_Backward(CTreeNode** node)
{
    if (!node || !(*node)) {
        return;
    }

    if (__is_header(*node)) {
        // node is End() of tree
        *node = (*node)->right;
    }
    else if ((*node)->left) {
        *node = __maximum((*node)->left);
    }
    else {
        CTreeNode* parent = (*node)->parent;
        while (parent->left == *node) {
            *node = parent;
            parent = parent->parent;
        }

        *node = parent;
    }
}

bool CTREE_Empty(CTree* tree)
{
    if (!tree) {
        return true;
    }

    return tree->node_count == 0;
}

size_t CTREE_Size(CTree* tree)
{
    if (!tree) {
        return 0;
    }

    return tree->node_count;
}

size_t CTREE_MaxSize(void)
{
    return (-1);
}

CTreeNode* CTREE_InsertEqual(CTree* tree, CReferencePtr data)
{
    if (!tree || !data) {
        return NULL;
    }

    CTreeNode* y = tree->header;
    CTreeNode* x = __root(tree);
    CCompare key_compare = tree->key_compare;
    while (x) {
        y = x;
        x = key_compare(data, x->data) ? x->left : x->right;
    }

    return __insert(tree, y, data);
}

CTreeNode* CTREE_InsertUnique(CTree* tree, CReferencePtr data)
{
    if (!tree || !data) {
        return NULL;
    }

    CTreeNode* y = tree->header;
    CTreeNode* x = __root(tree);
    CCompare key_compare = tree->key_compare;
    bool comp = true;
    while (x) {
        y = x;
        comp = key_compare(data, x->data);
        x = comp ? x->left : x->right;
    }

    CTreeNode* z = y;
    if (comp) {
        if (z == CTREE_Begin(tree)) {
            return __insert(tree, y, data);
        }
        else {
            CTREE_Backward(&z);
        }
    }

    if (key_compare(z->data, data)) {
        return __insert(tree, y, data);
    }

    return NULL;
}

void CTREE_Erase(CTree* tree, CTreeNode* node)
{
    if (!tree || !node) {
        return;
    }

    CTreeNode* erase_node = node;
    CTreeNode* replace_node = NULL;
    if (!__has_left(erase_node)) {
        // erase_node has right child or no child
        // replace_node may be null
        replace_node = __right(erase_node);
    }
    else {
        if (!__has_right(erase_node)) {
            // erase_node has left child
            replace_node = __left(erase_node);
            assert(replace_node);
        }
        else {
            // erase_node has both children
            // replace_node may be null
            erase_node = __minimum(__right(erase_node));
            replace_node = __right(erase_node);
        }
    }
    assert(erase_node);

    if (erase_node == node) { // replace erase_node with replace_node
        if (__root(tree) == erase_node) {
            __set_root(tree, replace_node);
        }
        else {
            if (__is_left(erase_node)) {
                __parent(erase_node)->left = replace_node;
            }
            else {
                __parent(erase_node)->right = replace_node;
            }
        }

        if (__leftmost(tree) == erase_node) {
            __set_leftmost(tree, replace_node ? __minimum(replace_node)
                                              : __parent(erase_node));
        }

        if (__rightmost(tree) == erase_node) {
            __set_rightmost(tree, replace_node ? __maximum(replace_node)
                                               : __parent(erase_node));
        }

        if (replace_node) {
            replace_node->parent = __parent(erase_node);
        }
    }
    else { // erase_node is node's successor
        if (__root(tree) == node) {
            __set_root(tree, erase_node);
        }
        else {
            if (__is_left(node)) {
                __parent(node)->left = erase_node;
            }
            else {
                __parent(node)->right = erase_node;
            }
        }

        erase_node->left = __left(node);
        __left(node)->parent = erase_node;
        if (erase_node != __right(node)) {
            erase_node->right = __right(node);
            __right(node)->parent = erase_node;
            __parent(erase_node)->left = replace_node;
            if (replace_node) {
                replace_node->parent = __parent(erase_node);
            }
        }

        erase_node->parent = __parent(node);
        erase_node = node;
    }

    __destroy_node(erase_node);
}

void CTREE_Clear(CTree* tree)
{
    if (!tree) {
        return;
    }

    __erase(__root(tree));
    CTreeNode* header = tree->header;
    header->parent = NULL;
    header->left = header;
    header->right = header;
    tree->node_count = 0;
}

CTreeNode* CTREE_Find(CTree* tree, CReferencePtr data)
{
    if (CTREE_Empty(tree) || !data) {
        return CTREE_End(tree);
    }

    CCompare key_compare = tree->key_compare;
    CTreeNode* node = __root(tree);
    while (node) {
        if (key_compare(data, node->data)) {
            node = node->left;
        }
        else {
            if (!key_compare(node->data, data)) {
                return node;
            }

            node = node->right;
        }
    }

    return CTREE_End(tree);
}
