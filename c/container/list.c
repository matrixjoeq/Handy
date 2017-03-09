

#include <stdlib.h>
#include <assert.h>
#include "list.h"

STATIC CListNode* createNode(CListNode** node)
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
    (*node)->data = NULL;

    return *node;
}

STATIC void popNode(CListNode* node)
{
    if (!node) {
        return;
    }

    node->next->prev = node->prev;
    node->prev->next = node->next;
    FREE(node->data);
    FREE(node);
}

CList* CLIST_CreateList(CList** list)
{
    if (!list || *list) {
        return NULL;
    }

    *list = (CList*) malloc(sizeof(CList));
    if (!(*list)) {
        return NULL;
    }

    (*list)->node = NULL;
    if (!createNode(&((*list)->node))) {
        FREE(*list);
        return NULL;
    }

    (*list)->node->prev = (*list)->node;
    (*list)->node->next = (*list)->node;

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

void CLIST_PushBack(CList* list, CReferencePtr data)
{
    if (!list || !data) {
        return;
    }

    CListNode* node = NULL;
    if (!createNode(&node)) {
        return;
    }

    node->data = data;
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

    popNode(list->node->prev);
}

void CLIST_PushFront(CList* list, CReferencePtr data)
{
    if (!list || !data) {
        return;
    }

    CListNode* node = NULL;
    if (!createNode(&node)) {
        return;
    }

    node->data = data;
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

    popNode(list->node->next);
}

void CLIST_Insert(CList* list, CListNode* pos, CReferencePtr data)
{
    if (!list || !pos || !data) {
        return;
    }

    CListNode* node = NULL;
    if (!createNode(&node)) {
        return;
    }

    node->data = data;
    node->next = pos;
    node->prev = pos->prev;
    pos->prev->next = node;
    pos->prev = node;
}

void CLIST_Erase(CList* list, CListNode* pos)
{
    if (!list || !pos) {
        return;
    }

    popNode(pos);
}

void CLIST_Remove(CList* list, CReferencePtr data)
{
    CListNode* node = CLIST_Find(list, data);
    popNode(node);
}

void CLIST_RemoveIf(CList* list, CReferencePtr data, CPredicate pred)
{
    CListNode* node = CLIST_FindIf(list, data, pred);
    popNode(node);
}

CListNode* CLIST_Find(CList* list, CReferencePtr data)
{
    if (!list || !data) {
        return NULL;
    }

    for (CListNode* node = CLIST_Begin(list);
            node != CLIST_End(list);
            node = node->next) {
        assert(node);
        if (data == node->data) {
            return node;
        }
    }

    return NULL;
}

CListNode* CLIST_FindIf(CList* list, CReferencePtr data, CPredicate pred)
{
    if (!pred) {
        return CLIST_Find(list, data);
    }

    for (CListNode* node = CLIST_Begin(list);
            node != CLIST_End(list);
            node = node->next) {
        assert(node);
        if (pred(data, node->data)) {
            return node;
        }
    }

    return NULL;
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

void CLIST_ForEachEx(CListNode* first, CListNode* last, CUserDataPtr userData, CBinaryFunction func)
{
    if (!first || !last || !func) {
        return;
    }

    for (CListNode* node = first; node != last; node = node->next) {
        assert(node);
        func(node->data, userData);
    }

    return;
}