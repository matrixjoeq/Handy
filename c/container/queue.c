
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

CQueue* CQUEUE_CreateQueue(CQueue** queue)
{
    if (!queue || *queue) {
        return NULL;
    }

    *queue = (CQueue*) malloc(sizeof(CQueue));
    if (!(*queue)) {
        return NULL;
    }

    (*queue)->sequence = NULL;
    if (!CLIST_CreateList(&((*queue)->sequence), NULL)) {
        FREE(*queue);
        return NULL;
    }

    return *queue;
}

void CQUEUE_DestroyQueue(CQueue* queue)
{
    if (!queue) {
        return;
    }

    CLIST_DestroyList(queue->sequence);
    FREE(queue);

    return;
}

CReferencePtr CQUEUE_Front(CQueue* queue)
{
    return queue ? CLIST_Front(queue->sequence) : NULL;
}

CReferencePtr CQUEUE_Back(CQueue* queue)
{
    return queue ? CLIST_Back(queue->sequence) : NULL;
}

bool CQUEUE_Empty(CQueue* queue)
{
    return queue ? CLIST_Empty(queue->sequence) : true;
}

size_t CQUEUE_Size(CQueue* queue)
{
    return queue ? CLIST_Size(queue->sequence) : 0;
}

void CQUEUE_Push(CQueue* queue, CReferencePtr data)
{
    if (!queue) {
        return;
    }

    CLIST_PushBack(queue->sequence, data);
}

void CQUEUE_Pop(CQueue* queue)
{
    if (!queue) {
        return;
    }

    CLIST_PopFront(queue->sequence);
}
