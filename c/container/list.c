

#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct __c_list_node {
    struct __c_list_node* prev;
    struct __c_list_node* next;
    CReferencePtr data;
};

struct __c_list {
    CListNode* node;
    CCompare compare;
};

STATIC CListNode* __create_node(CListNode** node, CReferencePtr data)
{
    if (!node || *node) {
        return NULL;
    }

    *node = (CListNode*) malloc(sizeof(CListNode));
    if (!(*node)) {
        return NULL;
    }

    (*node)->prev = NULL;
    (*node)->next = NULL;
    (*node)->data = data;

    return *node;
}

STATIC void __pop_node(CListNode* node)
{
    if (!node) {
        return;
    }

    node->next->prev = node->prev;
    node->prev->next = node->next;
    FREE(node->data);
    FREE(node);
}

STATIC INLINE CListNode* __decrement(CListNode* node)
{
    return node->prev;
}

STATIC INLINE CListNode* __increment(CListNode* node)
{
    return node->next;
}

STATIC bool __compare(CReferencePtr lhs, CReferencePtr rhs)
{
    return (lhs < rhs);
}

/**
 * constructor/destructor
 */
CList* CLIST_CreateList(CList** list, CCompare comp)
{
    if (!list || *list) {
        return NULL;
    }

    *list = (CList*) malloc(sizeof(CList));
    if (!(*list)) {
        return NULL;
    }

    (*list)->node = NULL;
    if (!__create_node(&((*list)->node), NULL)) {
        FREE(*list);
        return NULL;
    }

    (*list)->node->prev = (*list)->node;
    (*list)->node->next = (*list)->node;
    (*list)->compare = comp ? comp : __compare;

    return *list;
}

void CLIST_DestroyList(CList* list)
{
    if (!list) {
        return;
    }

    for (CListNode* node = list->node->next;
         node != list->node;
         ) {
        assert(node);
        CListNode* tmp = node->next;
        FREE(node->data);
        FREE(node);
        node = tmp;
    }

    FREE(list->node);
    FREE(list);

    return;
}

/**
 * element access
 */
CReferencePtr CLIST_Front(CList* list)
{
    if (CLIST_Empty(list)) {
        return NULL;
    }

    return list->node->next->data;
}

CReferencePtr CLIST_Back(CList* list)
{
    if (CLIST_Empty(list)) {
        return NULL;
    }

    return list->node->prev->data;
}

CReferencePtr CLIST_Reference(CListNode* node)
{
    return node ? node->data : NULL;
}

/**
 * iterators
 */
CListNode* CLIST_Begin(CList* list)
{
    return list ? list->node->next : NULL;
}

CListNode* CLIST_End(CList* list)
{
    return list ? list->node : NULL;
}

void CLIST_Forward(CListNode** node)
{
    if (!node || !(*node)) {
        return;
    }

    *node = (*node)->next;
}

void CLIST_Backward(CListNode** node)
{
    if (!node || !(*node)) {
        return;
    }

    *node = (*node)->prev;
}

/**
 * capacity
 */
bool CLIST_Empty(CList* list)
{
    return list ? CLIST_Begin(list) == CLIST_End(list) : true;
}

size_t CLIST_Size(CList *list)
{
    size_t size = 0;
    for (CListNode* node = CLIST_Begin(list);
         node != CLIST_End(list);
         node = node->next) {
        assert(node);
        ++size;
    }

    return size;
}

size_t CLIST_MaxSize(void)
{
    return (-1);
}

/**
 * modifiers
 */
void CLIST_PushBack(CList* list, CReferencePtr data)
{
    if (!list || !data) {
        return;
    }

    CListNode* node = NULL;
    if (!__create_node(&node, data)) {
        return;
    }

    node->next = list->node;
    node->prev = list->node->prev;
    list->node->prev->next = node;
    list->node->prev = node;
}

void CLIST_PopBack(CList* list)
{
    if (CLIST_Empty(list)) {
        return;
    }

    __pop_node(list->node->prev);
}

void CLIST_PushFront(CList* list, CReferencePtr data)
{
    if (!list || !data) {
        return;
    }

    CListNode* node = NULL;
    if (!__create_node(&node, data)) {
        return;
    }

    node->next = list->node->next;
    node->prev = list->node;
    list->node->next->prev = node;
    list->node->next = node;
}

void CLIST_PopFront(CList* list)
{
    if (CLIST_Empty(list)) {
        return;
    }

    __pop_node(list->node->next);
}

CListNode* CLIST_Insert(CList* list, CListNode* pos, CReferencePtr data)
{
    if (!list || !pos || !data) {
        return NULL;
    }

    CListNode* node = NULL;
    if (!__create_node(&node, data)) {
        return NULL;
    }

    node->next = pos;
    node->prev = pos->prev;
    pos->prev->next = node;
    pos->prev = node;

    return node;
}

void CLIST_Erase(CList* list, CListNode* pos)
{
    if (!list || !pos) {
        return;
    }

    __pop_node(pos);
}

/**
 * operations
 */
void CLIST_Remove(CList* list, CReferencePtr data)
{
    CListNode* node = CLIST_Find(list, data);
    while (node != CLIST_End(list)) {
        __pop_node(node);
        node = CLIST_Find(list, data);
    }
}

void CLIST_RemoveIf(CList* list, CUnaryPredicate pred)
{
    CListNode* node = CLIST_FindIf(list, pred);
    while (node != CLIST_End(list)) {
        __pop_node(node);
        node = CLIST_FindIf(list, pred);
    }
}

void CLIST_Sort(CList* list, CCompare comp)
{
    if (CLIST_Empty(list) || CLIST_Size(list) == 1) {
        return;
    }

    /*
    INSERT-SORT(A):
    for (i=1; i<length(A); ++i) {
        key=A[i]; // key is the value to be inserted
        j=i-1;
        while (j>=0 && key<A[j]) {
            // sort in low priority order
            // >A[j], sort in high priority order
            A[j+1]=A[j];
            --j;
        }
        A[j+1]=key;
    }
    */
    CCompare compare = comp ? comp : list->compare;
    // start from the second element
    for (CListNode* i = list->node->next->next; i != list->node; i = i->next) {
        CReferencePtr key = i->data;
        CListNode* j = i->prev;
        while (j != list->node && compare(key, j->data)) {
            j->next->data = j->data;
            j = j->prev;
        }
        j->next->data = key;
    }
}

void CLIST_Reverse(CList* list)
{
    if (CLIST_Empty(list) || CLIST_Size(list) == 1) {
        return;
    }

    CListNode* x = list->node->next;
    CListNode* y = NULL;
    while (x != list->node) {
        y = x->next;
        x->next = x->prev;
        x->prev = y;
        x = y;
    }

    y = list->node->next;
    list->node->next = list->node->prev;
    list->node->prev = y;
}

void CLIST_Unique(CList* list, CBinaryPredicate pred)
{
    if (CLIST_Empty(list) || CLIST_Size(list) == 1 || !pred) {
        return;
    }

    CListNode* x = list->node->next;
    CListNode* y = NULL;
    while (x != list->node && x->next != list->node) {
        y = x->next;
        if (pred(x->data, y->data)) {
            x->next = y->next;
            y->next->prev = x;
            __pop_node(y);
        }
        x = x->next;
    }
}

/**
 * algorithms
 */
CListNode* CLIST_Find(CList* list, CReferencePtr data)
{
    if (CLIST_Empty(list) || !data) {
        return CLIST_End(list);
    }

    CCompare compare = list->compare;
    for (CListNode* node = CLIST_Begin(list);
         node != CLIST_End(list);
         node = node->next) {
        assert(node);
        if (!compare(node->data, data) &&
            !compare(data, node->data)) {
            return node;
        }
    }

    return CLIST_End(list);
}

CListNode* CLIST_FindIf(CList* list, CUnaryPredicate pred)
{
    if (CLIST_Empty(list) || !pred) {
        return CLIST_End(list);
    }

    for (CListNode* node = CLIST_Begin(list);
         node != CLIST_End(list);
         node = node->next) {
        assert(node);
        if (pred(node->data)) {
            return node;
        }
    }

    return CLIST_End(list);
}

void CLIST_ForEach(CListNode* first, CListNode* last, CUnaryFunction func)
{
    if (!first || !last || !func) {
        return;
    }

    for (CListNode* node = first; node != last; node = node->next) {
        assert(node);
        func(node->data);
    }

    return;
}
