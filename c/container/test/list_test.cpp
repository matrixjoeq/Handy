
#include <gtest/gtest.h>
#include "list.h"

namespace handy {
namespace c {

namespace {

using ::testing::TestWithParam;
using ::testing::ValuesIn;

#define CREATE_LIST(__list) \
    CList* __list = nullptr; \
    CLIST_CreateList(&__list, Less<int>); \
    EXPECT_NE(__list, nullptr)

#define DESTROY_LIST(__list) \
    CLIST_DestroyList(__list); \
    __list = nullptr

const uint32_t MAX_NUMBER = 10;

struct Param {
    int numbers[MAX_NUMBER];
};

const Param params[] = {
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
    { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4 }
};

template<typename T, int N>
bool Equal(CReferencePtr data)
{
    T* data_ = reinterpret_cast<T*>(data);

    return (*data_ == N);
}

template<typename T>
bool Less(CReferencePtr lhs, CReferencePtr rhs)
{
    T* lhs_ = reinterpret_cast<T*>(lhs);
    T* rhs_ = reinterpret_cast<T*>(rhs);

    return (*lhs_ < *rhs_);
}

class CListTestModifier : public TestWithParam<struct Param> {};
class CListTestOperation : public TestWithParam<struct Param> {};
class CListTestAlgorithm : public TestWithParam<struct Param> {};

TEST(CListTest, CreateDestroy)
{
    CList* list = nullptr;
    CList* ret = CLIST_CreateList(&list, Less<int>);
    EXPECT_EQ(ret, list);
    EXPECT_NE(list, nullptr);
    EXPECT_TRUE(CLIST_Empty(list));
    EXPECT_EQ(CLIST_Size(list), 0);
    EXPECT_EQ(CLIST_Begin(list), CLIST_End(list));

    DESTROY_LIST(list);
}

TEST(CListTest, Iterator)
{
    int value = 0;
    CREATE_LIST(list);
    CREATE_DATA(first, int, value);
    CLIST_PushBack(list, first);
    CListNode* it = CLIST_Begin(list);
    EXPECT_EQ(CLIST_Reference(it), first);
    CLIST_Forward(&it);
    EXPECT_EQ(CLIST_End(list), it);
    CLIST_Backward(&it);
    EXPECT_EQ(CLIST_Begin(list), it);

    value = 1;
    CREATE_DATA(second, int, value);
    CLIST_PushBack(list, second);
    CLIST_Forward(&it);
    EXPECT_EQ(CLIST_Reference(it), second);
    CLIST_Forward(&it);
    EXPECT_EQ(CLIST_End(list), it);
    CLIST_Backward(&it);
    EXPECT_EQ(CLIST_Reference(it), second);
    CLIST_Backward(&it);
    EXPECT_EQ(CLIST_Reference(it), first);

    DESTROY_LIST(list);
}

TEST_P(CListTestModifier, PushPopReferenceBack)
{
    Param param = GetParam();
    CREATE_LIST(list);

    ARRAY_FOREACH(param.numbers, i) {
        CREATE_DATA(num, int, param.numbers[i]);
        CLIST_PushBack(list, num);
        EXPECT_FALSE(CLIST_Empty(list));
        EXPECT_EQ(CLIST_Size(list), i + 1);
        EXPECT_EQ(CLIST_Back(list), num);
        EXPECT_NE(CLIST_Begin(list), CLIST_End(list));
    }

    while (!CLIST_Empty(list)) {
        size_t size = CLIST_Size(list);
        CReferencePtr back = CLIST_Back(list);
        EXPECT_NE(CLIST_Begin(list), CLIST_End(list));
        CLIST_PopBack(list);
        EXPECT_EQ(CLIST_Size(list), size - 1);
        EXPECT_NE(CLIST_Back(list), back);
    }

    DESTROY_LIST(list);
}

TEST_P(CListTestModifier, PushPopReferenceFront)
{
    Param param = GetParam();
    CREATE_LIST(list);

    ARRAY_FOREACH(param.numbers, i) {
        CREATE_DATA(num, int, param.numbers[i]);
        CLIST_PushFront(list, num);
        EXPECT_FALSE(CLIST_Empty(list));
        EXPECT_EQ(CLIST_Size(list), i + 1);
        EXPECT_EQ(CLIST_Front(list), num);
        EXPECT_NE(CLIST_Begin(list), CLIST_End(list));
    }

    while (!CLIST_Empty(list)) {
        size_t size = CLIST_Size(list);
        CReferencePtr front = CLIST_Front(list);
        EXPECT_NE(CLIST_Begin(list), CLIST_End(list));
        CLIST_PopFront(list);
        EXPECT_EQ(CLIST_Size(list), size - 1);
        EXPECT_NE(CLIST_Front(list), front);
    }

    DESTROY_LIST(list);
}

TEST_P(CListTestModifier, InsertErase)
{
    Param param = GetParam();
    CREATE_LIST(list);

    ARRAY_FOREACH(param.numbers, i) {
        CREATE_DATA(num, int, param.numbers[i]);
        CListNode* node = CLIST_Insert(list, CLIST_Begin(list), num);
        EXPECT_FALSE(CLIST_Empty(list));
        EXPECT_EQ(CLIST_Size(list), i + 1);
        EXPECT_EQ(CLIST_Begin(list), node);
        EXPECT_EQ(CLIST_Reference(node), num);
    }

    while (!CLIST_Empty(list)) {
        CListNode* begin = CLIST_Begin(list);
        size_t size = CLIST_Size(list);
        CLIST_Erase(list, CLIST_Begin(list));
        EXPECT_NE(CLIST_Begin(list), begin);
        EXPECT_EQ(CLIST_Size(list), size - 1);
    }

    DESTROY_LIST(list);
}

TEST_P(CListTestOperation, Remove)
{
    Param param = GetParam();
    CREATE_LIST(list);

    ARRAY_FOREACH(param.numbers, i) {
        CREATE_DATA(num, int, param.numbers[i]);
        CLIST_PushBack(list, num);
    }

    while (!CLIST_Empty(list)) {
        CReferencePtr data = CLIST_Front(list);
        CLIST_Remove(list, data);
        EXPECT_EQ(CLIST_End(list), CLIST_Find(list, data));
    }

    DESTROY_LIST(list);
}

TEST_P(CListTestOperation, RemoveIf)
{
    Param param = GetParam();
    CREATE_LIST(list);

    ARRAY_FOREACH(param.numbers, i) {
        CREATE_DATA(num, int, param.numbers[i]);
        CLIST_PushBack(list, num);
    }

    CLIST_RemoveIf(list, Equal<int, 4>);
    EXPECT_EQ(CLIST_End(list), CLIST_FindIf(list, Equal<int, 4>));

    DESTROY_LIST(list);
}

TEST_P(CListTestAlgorithm, Find)
{
    Param param = GetParam();
    CREATE_LIST(list);

    ARRAY_FOREACH(param.numbers, i) {
        CREATE_DATA(num, int, param.numbers[i]);
        CLIST_PushBack(list, num);
        EXPECT_NE(CLIST_End(list), CLIST_Find(list, num));
    }

    DESTROY_LIST(list);
}

TEST_P(CListTestAlgorithm, FindIf)
{
    Param param = GetParam();
    CREATE_LIST(list);

    ARRAY_FOREACH(param.numbers, i) {
        CREATE_DATA(num, int, param.numbers[i]);
        CLIST_PushBack(list, num);
    }

    // TODO

    DESTROY_LIST(list);
}

TEST_P(CListTestAlgorithm, ForEach)
{
    Param param = GetParam();
    CREATE_LIST(list);

    ARRAY_FOREACH(param.numbers, i) {
        CREATE_DATA(num, int, param.numbers[i]);
        CLIST_PushBack(list, num);
    }

    // TODO
    //CLIST_ForEach(CLIST_Begin(list), CLIST_End(list), Do);

    DESTROY_LIST(list);
}

TEST_P(CListTestAlgorithm, ForEachEx)
{
    Param param = GetParam();
    CREATE_LIST(list);

    ARRAY_FOREACH(param.numbers, i) {
        CREATE_DATA(num, int, param.numbers[i]);
        CLIST_PushBack(list, num);
    }

    // TODO

    DESTROY_LIST(list);
}

INSTANTIATE_TEST_CASE_P(CListTest, CListTestModifier, ValuesIn(params));
INSTANTIATE_TEST_CASE_P(CListTest, CListTestOperation, ValuesIn(params));
INSTANTIATE_TEST_CASE_P(CListTest, CListTestAlgorithm, ValuesIn(params));

} // namespace
} // namespace c
} // namespace handy
