

#ifndef __HANDY_C_CONTAINER_LIST_H
#define __HANDY_C_CONTAINER_LIST_H

#include <stdbool.h>
#include <stddef.h>
#include "shared_types.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct __c_list_node;
typedef struct __c_list_node* CListIterator;

struct __c_list;
typedef struct __c_list CList;

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
CReferencePtr CLIST_Reference(CListIterator iter);

/**
 * iterators
 */
CListIterator CLIST_Begin(CList* list);
CListIterator CLIST_End(CList* list);
void CLIST_Forward(CListIterator* iter);
void CLIST_Backward(CListIterator* iter);

/**
 * capacity
 */
bool CLIST_Empty(CList* list);
size_t CLIST_Size(CList* list);
size_t CLIST_MaxSize(void);

/**
 * modifiers
 */
void CLIST_Clear(CList* list);
CListIterator CLIST_Insert(CList* list, CListIterator pos, CReferencePtr data);
CListIterator CLIST_Erase(CList* list, CListIterator pos);
void CLIST_PushBack(CList* list, CReferencePtr data);
void CLIST_PopBack(CList* list);
void CLIST_PushFront(CList* list, CReferencePtr data);
void CLIST_PopFront(CList* list);

/**
 * operations
 */
void CLIST_Remove(CList* list, CReferencePtr data);
void CLIST_RemoveIf(CList* list, CUnaryPredicate pred);
void CLIST_Sort(CList* list, CCompare comp);
void CLIST_Reverse(CList* list);
void CLIST_Unique(CList* list, CBinaryPredicate pred);

/**
 * algorithms
 */
CListIterator CLIST_Find(CList* list, CReferencePtr data);
CListIterator CLIST_FindIf(CList* list, CUnaryPredicate pred);
void CLIST_ForEach(CListIterator first, CListIterator last, CUnaryFunction func);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  // __HANDY_C_CONTAINER_LIST_H
