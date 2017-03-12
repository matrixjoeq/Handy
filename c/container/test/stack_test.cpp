
#include <gtest/gtest.h>
#include "shared_types.h"
#include "stack.h"

namespace handy {
namespace c {
namespace {

#define CREATE_STACK(__stack) \
    CStack* __stack = nullptr; \
    CSTACK_CreateStack(&__stack); \
    EXPECT_NE(__stack, nullptr)

#define DESTORY_STACK(__stack) \
    CSTACK_DestroyStack(__stack); \
    __stack = nullptr

TEST(CStackTest, CreateDestroy)
{
    CStack* stack = nullptr;
    CStack* ret = CSTACK_CreateStack(&stack);
    EXPECT_EQ(ret, stack);
    EXPECT_NE(stack, nullptr);
    EXPECT_TRUE(CSTACK_Empty(stack));
    EXPECT_EQ(CSTACK_Size(stack), 0);

    DESTORY_STACK(stack);
}

TEST(CStackTest, PushPopReference)
{
    CREATE_STACK(stack);
    int numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    ARRAY_FOREACH(numbers, i) {
        CREATE_DATA(num, int, numbers[i]);
        CSTACK_Push(stack, num);
        EXPECT_FALSE(CSTACK_Empty(stack));
        EXPECT_EQ(CSTACK_Size(stack), i + 1);
        EXPECT_EQ(CSTACK_Top(stack), num);
    }

    while (!CSTACK_Empty(stack)) {
        size_t size = CSTACK_Size(stack);
        CReferencePtr top = CSTACK_Top(stack);
        CSTACK_Pop(stack);
        EXPECT_EQ(CSTACK_Size(stack), size - 1);
        EXPECT_NE(CSTACK_Top(stack), top);
    }

    DESTORY_STACK(stack);
}

} // namespace
} // namespace c
} // namespace handy
