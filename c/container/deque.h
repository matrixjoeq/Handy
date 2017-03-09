

#ifndef __HANDY_C_CONTAINER_DEQUE_H
#define __HANDY_C_CONTAINER_DEQUE_H

#include <stdbool.h>
#include <stddef.h>
#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct __c_queue {
    CList* sequence;
} CQueue;

/**
 * constructor/destructor
 */
CQueue* CQUEUE_CreateQueue(CQueue** queue);
void CQUEUE_DestroyQueue(CQueue* queue);

/**
 * element access
 */
CReferencePtr CQUEUE_Front(CQueue* queue);
const CReferencePtr CQUEUE_FrontConst(CQueue* queue);
CReferencePtr CQUEUE_Back(CQueue* queue);
const CReferencePtr CQUEUE_BackConst(CQueue* queue);

/**
 * capacity
 */
bool CQUEUE_Empty(CQueue* queue);
size_t CQUEUE_Size(CQueue* queue);

/**
 * modifiers
 */
void CQUEUE_Push(CQueue* queue, CReferencePtr data);
void CQUEUE_Pop(CQueue* queue);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __HANDY_C_CONTAINER_DEQUE_H
