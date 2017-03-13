

#ifndef __HANDY_C_CONTAINER_LIST_H
#define __HANDY_C_CONTAINER_LIST_H

#include <stdbool.h>
#include <stddef.h>
#include "shared_types.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct __c_list_node {
    struct __c_list_node* prev;
    struct __c_list_node* next;
    CReferencePtr data;
} CListNode;

typedef struct __c_list {
    CListNode* node;
    CCompare compare;
} CList;

/**
 * constructor/destructor
 */
CList* CLIST_CreateList(CList** list, CCompare comp);
void CLIST_DestroyList(CList* list);

/**
 * element access
 */
CReferencePtr CLIST_Front(CList* list);
CReferencePtr CLIST_Back(CList* list);
CReferencePtr CLIST_Reference(CListNode* node);

/**
 * iterators
 */
CListNode* CLIST_Begin(CList* list);
CListNode* CLIST_End(CList* list);
void CLIST_Forward(CListNode** node);
void CLIST_Backward(CListNode** node);

/**
 * capacity
 */
bool CLIST_Empty(CList* list);
size_t CLIST_Size(CList* list);

/**
 * modifiers
 */
void CLIST_PushBack(CList* list, CReferencePtr data);
void CLIST_PopBack(CList* list);
void CLIST_PushFront(CList* list, CReferencePtr data);
void CLIST_PopFront(CList* list);
CListNode* CLIST_Insert(CList* list, CListNode* pos, CReferencePtr data);
void CLIST_Erase(CList* list, CListNode* pos);

/**
 * operations
 */
void CLIST_Remove(CList* list, CReferencePtr data);
void CLIST_RemoveIf(CList* list, CUnaryPredicate pred);

/**
 * algorithms
 */
CListNode* CLIST_Find(CList* list, CReferencePtr data);
CListNode* CLIST_FindIf(CList* list, CUnaryPredicate pred);
void CLIST_ForEach(CListNode* first, CListNode* last, CUnaryFunction func);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  // __HANDY_C_CONTAINER_LIST_H

