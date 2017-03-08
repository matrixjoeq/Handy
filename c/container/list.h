

#ifndef __HANDY_C_CONTAINER_LIST_H
#define __HANDY_C_CONTAINER_LIST_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* CListDataPtr;
typedef void* UserDataPtr;

typedef struct __c_list_node {
    struct __c_list_node* prev;
    struct __c_list_node* next;
    CListDataPtr data;
} CListNode;

typedef struct __c_list {
    CListNode* node;
} CList;

typedef void (*CLIST_DestroyHandler)(CListDataPtr data);
typedef void (*CLIST_UnaryFunction)(CListDataPtr data);
typedef void (*CLIST_BinaryFunction)(CListDataPtr data, UserDataPtr userData);
typedef bool (*CLIST_Predicate)(CListDataPtr data1, CListDataPtr data2);

/**
 * constructor/destructor
 */
CList* CLIST_CreateList(CList** list);
void CLIST_DestroyList(CList* list, CLIST_DestroyHandler handler);

/**
 * element access
 */
CListDataPtr CLIST_Front(CList* list);
CListDataPtr CLIST_Back(CList* list);
CListDataPtr CLIST_Reference(CListNode* node);

/**
 * iterators
 */
CListNode* CLIST_Begin(CList* list);
CListNode* CLIST_End(CList* list);
CListNode* CLIST_Forward(CListNode* node);
CListNode* CLIST_Backward(CListNode* node);

/**
 * capacity
 */
bool CLIST_Empty(CList* list);
size_t CLIST_Size(CList* list);

/**
 * modifiers
 */
CListNode* CLIST_PushBack(CList* list, CListDataPtr data);
CListDataPtr CLIST_PopBack(CList* list);
CListNode* CLIST_PushFront(CList* list, CListDataPtr data);
CListDataPtr CLIST_PopFront(CList* list);
CListNode* CLIST_Insert(CList* list, CListNode* pos, CListDataPtr data);
CListDataPtr CLIST_Erase(CList* list, CListNode* pos);

/**
 * operations
 */
CListDataPtr CLIST_Remove(CList* list, CListDataPtr data);
CListDataPtr CLIST_RemoveIf(CList* list, CListDataPtr data, CLIST_Predicate pred);

/**
 * algorithms
 */
CListNode* CLIST_Find(CList* list, CListDataPtr data);
CListNode* CLIST_FindIf(CList* list, CListDataPtr data, CLIST_Predicate pred);
void CLIST_ForEach(CListNode* first, CListNode* last, CLIST_UnaryFunction func);
void CLIST_ForEachEx(CListNode* first, CListNode* last, UserDataPtr userData, CLIST_BinaryFunction func);

#ifdef __cplusplus
}
#endif

#endif  // __HANDY_C_CONTAINER_LIST_H

