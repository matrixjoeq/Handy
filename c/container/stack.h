
#ifndef __HANDY_C_CONTAINER_STACK_H
#define __HANDY_C_CONTAINER_STACK_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct __c_stack;
typedef struct __c_stack CStack;

/**
 * constructor/destructor
 */
CStack* CSTACK_CreateStack(CStack** stack);
void CSTACK_DestroyStack(CStack* stack);

/**
 * element access
 */
CReferencePtr CSTACK_Top(CStack* stack);

/**
 * capacity
 */
bool CSTACK_Empty(CStack* stack);
size_t CSTACK_Size(CStack* stack);

/**
 * modifiers
 */
void CSTACK_Push(CStack* stack, CReferencePtr data);
void CSTACK_Pop(CStack* stack);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __HANDY_C_CONTAINER_STACK_H
