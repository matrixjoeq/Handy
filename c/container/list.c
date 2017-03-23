

#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct __c_list_node {
    struct __c_list_node* prev;
    struct __c_list_node* next;
    CReferencePtr data;
};

struct __c_list {
    struct __c_list_node* node;
    CCompare compare;
};

typedef struct __c_list_node CListNode;

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

STATIC CListNode* __pop_node(CListNode* node)
{
    assert(node);

    CListNode* next_node = node->next;
    CListNode* prev_node = node->prev;

    next_node->prev = prev_node;
    prev_node->next = next_node;
    FREE(node->data);
    FREE(node);

    return next_node;
}

STATIC INLINE CListIterator __decrement(CListIterator node)
{
    return node->prev;
}

STATIC INLINE CListIterator __increment(CListIterator node)
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

    CListNode* first = list->node->next;
    CListNode* last = list->node;
    CListNode* next = NULL;
    while (first != last) {
        assert(first);
        next = first->next;
        FREE(first->data);
        FREE(first);
        first = next;
    }

    FREE(last);
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

CReferencePtr CLIST_Reference(CListIterator iter)
{
    return iter ? iter->data : NULL;
}

/**
 * iterators
 */
CListIterator CLIST_Begin(CList* list)
{
    return (list ? list->node->next : NULL);
}

CListIterator CLIST_End(CList* list)
{
    return (list ? list->node : NULL);
}

void CLIST_Forward(CListIterator* iter)
{
    if (!iter || !(*iter)) {
        return;
    }

    *iter = (*iter)->next;
}

void CLIST_Backward(CListIterator* iter)
{
    if (!iter || !(*iter)) {
        return;
    }

    *iter = (*iter)->prev;
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
    for (CListIterator iter = CLIST_Begin(list);
         iter != CLIST_End(list);
         CLIST_Forward(&iter)) {
        assert(iter);
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

CListIterator CLIST_Insert(CList* list, CListIterator pos, CReferencePtr data)
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

    return (CListIterator)node;
}

CListIterator CLIST_Erase(CList* list, CListIterator pos)
{
    if (!list || !pos) {
        return NULL;
    }

    return (CListIterator)__pop_node((CListNode*)pos);
}

/**
 * operations
 */
void CLIST_Remove(CList* list, CReferencePtr data)
{
    CListIterator iter = CLIST_Find(list, data);
    while (iter != CLIST_End(list)) {
        __pop_node(iter);
        iter = CLIST_Find(list, data);
    }
}

void CLIST_RemoveIf(CList* list, CUnaryPredicate pred)
{
    CListIterator iter = CLIST_FindIf(list, pred);
    while (iter != CLIST_End(list)) {
        __pop_node(iter);
        iter = CLIST_FindIf(list, pred);
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
    for (CListIterator i = list->node->next->next; i != list->node; i = i->next) {
        CReferencePtr key = i->data;
        CListIterator j = i->prev;
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

    CListIterator x = list->node->next;
    CListIterator y = NULL;
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

    CListIterator x = list->node->next;
    CListIterator y = NULL;
    while (x != list->node && x->next != list->node) {
        y = x->next;
        while (y != list->node && pred(x->data, y->data)) {
            y = __pop_node(y);
        }
        x = x->next;
    }
}

/**
 * algorithms
 */
CListIterator CLIST_Find(CList* list, CReferencePtr data)
{
    if (CLIST_Empty(list) || !data) {
        return CLIST_End(list);
    }

    CCompare compare = list->compare;
    for (CListIterator iter = CLIST_Begin(list);
         iter != CLIST_End(list);
         CLIST_Forward(&iter)) {
        assert(iter);
        if (!compare(iter->data, data) &&
            !compare(data, iter->data)) {
            return iter;
        }
    }

    return CLIST_End(list);
}

CListIterator CLIST_FindIf(CList* list, CUnaryPredicate pred)
{
    if (CLIST_Empty(list) || !pred) {
        return CLIST_End(list);
    }

    for (CListIterator iter = CLIST_Begin(list);
         iter != CLIST_End(list);
         CLIST_Forward(&iter)) {
        assert(iter);
        if (pred(iter->data)) {
            return iter;
        }
    }

    return CLIST_End(list);
}

void CLIST_ForEach(CListIterator first, CListIterator last, CUnaryFunction func)
{
    if (!first || !last || !func) {
        return;
    }

    for (CListIterator iter = first; iter != last; CLIST_Forward(&iter)) {
        assert(iter);
        func(iter->data);
    }
}
