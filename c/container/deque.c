

#include <stdlib.h>
#include <assert.h>
#include "vector.h"
#include "deque.h"

struct __c_deque {
    CVector* sequence;
};

/**
 * constructor/destructor
 */
CDeque* CDEQUE_CreateDeque(CDeque** deque)
{
    UNUSE(deque);
    return NULL;
}

void CDEQUE_DestroyDeque(CDeque* deque)
{
    UNUSE(deque);
}

/**
 * element access
 */
CReferencePtr CDEQUE_Front(CDeque* deque)
{
    UNUSE(deque);
    return NULL;
}

CReferencePtr CDEQUE_Back(CDeque* deque)
{
    UNUSE(deque);
    return NULL;
}

/**
 * capacity
 */
bool CDEQUE_Empty(CDeque* deque)
{
    UNUSE(deque);
    return true;
}

size_t CDEQUE_Size(CDeque* deque)
{
    UNUSE(deque);
    return 0;
}

/**
 * modifiers
 */
void CDEQUE_Push(CDeque* deque, CReferencePtr data)
{
    UNUSE(deque);
    UNUSE(data);
}

void CDEQUE_Pop(CDeque* deque)
{
    UNUSE(deque);
}
