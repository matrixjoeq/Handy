
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

CStack* CSTACK_CreateStack(CStack** stack)
{
    if (!stack || *stack) {
        return NULL;
    }

    *stack = (CStack*) malloc(sizeof(CStack));
    if (!(*stack)) {
        return NULL;
    }

    (*stack)->sequence = NULL;
    if (!CLIST_CreateList(&((*stack)->sequence), NULL)) {
        FREE(*stack);
        return NULL;
    }

    return *stack;
}

void CSTACK_DestroyStack(CStack* stack)
{
    if (!stack) {
        return;
    }

    CLIST_DestroyList(stack->sequence);
    FREE(stack);

    return;
}

CReferencePtr CSTACK_Top(CStack* stack)
{
    return stack ? CLIST_Back(stack->sequence) : NULL;
}

bool CSTACK_Empty(CStack* stack)
{
    return stack ? CLIST_Empty(stack->sequence) : true;
}

size_t CSTACK_Size(CStack* stack)
{
    return stack ? CLIST_Size(stack->sequence) : 0;
}

void CSTACK_Push(CStack* stack, CReferencePtr data)
{
    if (!stack) {
        return;
    }

    CLIST_PushBack(stack->sequence, data);
}

void CSTACK_Pop(CStack* stack)
{
    if (!stack) {
        return;
    }

    CLIST_PopBack(stack->sequence);
}
