
#include <gtest/gtest.h>
#include "shared_types.h"
#include "queue.h"

namespace handy {
namespace c {
namespace {

#define CREATE_QUEUE(__queue) \
    CQueue* __queue = nullptr; \
    CQUEUE_CreateQueue(&__queue); \
    EXPECT_NE(__queue, nullptr)

#define DESTORY_QUEUE(__queue) \
    CQUEUE_DestroyQueue(__queue); \
    __queue = nullptr

TEST(CQueueTest, CreateDestroy)
{
    CQueue* queue = nullptr;
    CQueue* ret = CQUEUE_CreateQueue(&queue);
    EXPECT_EQ(ret, queue);
    EXPECT_NE(queue, nullptr);
    EXPECT_TRUE(CQUEUE_Empty(queue));
    EXPECT_EQ(CQUEUE_Size(queue), 0);

    DESTORY_QUEUE(queue);
}

TEST(CQueueTest, PushPopReference)
{
    CREATE_QUEUE(queue);
    int numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    ARRAY_FOREACH(numbers, i) {
        CREATE_DATA(num, int, numbers[i]);
        CQUEUE_Push(queue, num);
        EXPECT_FALSE(CQUEUE_Empty(queue));
        EXPECT_EQ(CQUEUE_Size(queue), i + 1);
        EXPECT_EQ(CQUEUE_Back(queue), num);
    }

    while (!CQUEUE_Empty(queue)) {
        size_t size = CQUEUE_Size(queue);
        CReferencePtr front = CQUEUE_Front(queue);
        CQUEUE_Pop(queue);
        EXPECT_EQ(CQUEUE_Size(queue), size - 1);
        EXPECT_NE(CQUEUE_Front(queue), front);
    }

    DESTORY_QUEUE(queue);
}

} // namespace
} // namespace c
} // namespace handy
