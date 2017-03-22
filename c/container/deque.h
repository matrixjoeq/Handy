

#ifndef __HANDY_C_CONTAINER_DEQUE_H
#define __HANDY_C_CONTAINER_DEQUE_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct __c_deque CDeque;

/**
 * constructor/destructor
 */
CDeque* CDEQUE_CreateDeque(CDeque** deque);
void CDEQUE_DestroyDeque(CDeque* deque);

/**
 * element access
 */
CReferencePtr CDEQUE_Front(CDeque* deque);
CReferencePtr CDEQUE_Back(CDeque* deque);

/**
 * capacity
 */
bool CDEQUE_Empty(CDeque* deque);
size_t CDEQUE_Size(CDeque* deque);

/**
 * modifiers
 */
void CDEQUE_Push(CDeque* deque, CReferencePtr data);
void CDEQUE_Pop(CDeque* deque);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __HANDY_C_CONTAINER_DEQUE_H
