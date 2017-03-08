

#include <stdlib.h>
#include <assert.h>
#include "list.h"

#ifndef UNIT_TEST
#define STATIC static
#else
#define STATIC
#endif

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

STATIC CListDataPtr popNode(CListNode* node)
{
    if (!node) {
        return NULL;
    }

    CListDataPtr data = node->data;
    node->next->prev = node->prev;
    node->prev->next = node->next;
    free(node);

    return data;
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
        free(*list);
        *list = NULL;
        return NULL;
    }

    (*list)->node->prev = (*list)->node;
    (*list)->node->next = (*list)->node;

    return *list;
}

void CLIST_DestroyList(CList* list, CLIST_DestroyHandler handler)
{
    if (!list) {
        return;
    }

    for (CListNode* node = list->node->next;
         node != list->node;
         ) {
        assert(node);
        assert(handler);
        handler(node->data);
        CListNode* tmp = node->next;
        free(node);
        node = tmp;
    }

    free(list->node);
    free(list);

    return;
}

CListDataPtr CLIST_Front(CList* list)
{
    if (CLIST_Empty(list)) {
        return NULL;
    }

    return list->node->next->data;
}

CListDataPtr CLIST_Back(CList* list)
{
    if (CLIST_Empty(list)) {
        return NULL;
    }

    return list->node->prev->data;
}

CListDataPtr CLIST_Reference(CListNode* node)
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

CListNode* CLIST_Forward(CListNode* node)
{    
    return node == NULL ? NULL : node->next;
}

CListNode* CLIST_Backward(CListNode* node)
{
    return node == NULL ? NULL : node->prev;
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

CListNode* CLIST_PushBack(CList* list, CListDataPtr data)
{
    if (!list || !data) {
        return NULL;
    }

    CListNode* node = NULL;
    if (!createNode(&node)) {
        return NULL;
    }

    node->data = data;
    node->next = list->node;
    node->prev = list->node->prev;
    list->node->prev->next = node;
    list->node->prev = node;

    return node;
}

CListDataPtr CLIST_PopBack(CList* list)
{
    if (CLIST_Empty(list)) {
        return NULL;
    }

    return popNode(list->node->prev);
}

CListNode* CLIST_PushFront(CList* list, CListDataPtr data)
{
    if (!list || !data) {
        return NULL;
    }

    CListNode* node = NULL;
    if (!createNode(&node)) {
        return NULL;
    }

    node->data = data;
    node->next = list->node->next;
    node->prev = list->node;
    list->node->next->prev = node;
    list->node->next = node;

    return node;
}

CListDataPtr CLIST_PopFront(CList* list)
{
    if (CLIST_Empty(list)) {
        return NULL;
    }

    return popNode(list->node->next);
}

CListNode* CLIST_Insert(CList* list, CListNode* pos, CListDataPtr data)
{
    if (!list || !pos || !data) {
        return NULL;
    }

    CListNode* node = NULL;
    if (!createNode(&node)) {
        return NULL;
    }

    node->data = data;
    node->next = pos;
    node->prev = pos->prev;
    pos->prev->next = node;
    pos->prev = node;

    return node;
}

CListDataPtr CLIST_Erase(CList* list, CListNode* pos)
{
    if (!list || !pos) {
        return NULL;
    }

    return popNode(pos);
}

CListDataPtr CLIST_Remove(CList* list, CListDataPtr data)
{
    CListNode* node = CLIST_Find(list, data);
    return popNode(node);
}

CListDataPtr CLIST_RemoveIf(CList* list, CListDataPtr data, CLIST_Predicate pred)
{
    CListNode* node = CLIST_FindIf(list, data, pred);
    return popNode(node);
}

CListNode* CLIST_Find(CList* list, CListDataPtr data)
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

CListNode* CLIST_FindIf(CList* list, CListDataPtr data, CLIST_Predicate pred)
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

void CLIST_ForEach(CListNode* first, CListNode* last, CLIST_UnaryFunction func)
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

void CLIST_ForEachEx(CListNode* first, CListNode* last, UserDataPtr userData, CLIST_BinaryFunction func)
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
