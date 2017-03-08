
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

#ifndef UNIT_TEST
#define STATIC static
#else
#define STATIC
#endif


CStack* CSTACK_CreateStack(CStack** stack)
{
    if (!stack || *stack) {
        return NULL;
    }

    *stack = (CStack*) malloc(sizeof(CStack));
    if (!(*stack)) {
        return NULL;
    }
    
    if (!CLIST_CreateList(&((*stack)->sequence))) {
        free(*stack);
        return NULL;
    }
    
    return *stack;
}

void CSTACK_DestroyStack(CStack* stack, CSTACK_DestroyHandler handler)
{
    if (!stack) {
        return;
    }

    CLIST_DestroyList(stack->sequence, (CLIST_DestroyHandler)handler);
    free(stack);

    return;
}

CStackDataPtr CSTACK_Top(CStack* stack)
{
    return stack ? (CStackDataPtr)CLIST_Back(stack->sequence) : NULL;
}

const CStackDataPtr CSTACK_TopConst(CStack* stack)
{
    return stack ? (CStackDataPtr)CLIST_Back(stack->sequence) : NULL;
}

bool CSTACK_Empty(CStack* stack)
{
    return stack ? CLIST_Empty(stack->sequence) : true;
}

size_t CSTACK_Size(CStack* stack)
{
    return stack ? CLIST_Size(stack->sequence) : 0;
}

void CSTACK_Push(CStack* stack, CStackDataPtr data)
{
    if (!stack) {
        return;
    }
    
    CLIST_PushBack(stack->sequence, (CListDataPtr)data);
}

CStackDataPtr CSTACK_Pop(CStack* stack)
{
    return stack ? (CStackDataPtr)CLIST_PopBack(stack->sequence) : NULL;
}
