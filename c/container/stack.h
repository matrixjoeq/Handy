
#ifndef __HANDY_C_CONTAINER_STACK_H
#define __HANDY_C_CONTAINER_STACK_H

#include <stdbool.h>
#include <stddef.h>
#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef void* CStackDataPtr;
typedef struct __c_stack {
    CList* sequence;
} CStack;

typedef void (*CSTACK_DestroyHandler)(CStackDataPtr data);

/**
 * constructor/destructor
 */
CStack* CSTACK_CreateStack(CStack** stack);
void CSTACK_DestroyStack(CStack* stack, CSTACK_DestroyHandler handler);

/**
 * element access
 */
CStackDataPtr CSTACK_Top(CStack* stack);
const CStackDataPtr CSTACK_TopConst(CStack* stack);

/**
 * capacity
 */
bool CSTACK_Empty(CStack* stack);
size_t CSTACK_Size(CStack* stack);

/**
 * modifiers
 */
void CSTACK_Push(CStack* stack, CStackDataPtr data);
CStackDataPtr CSTACK_Pop(CStack* stack);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __HANDY_C_CONTAINER_STACK_H
