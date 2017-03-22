
#include <gtest/gtest.h>
#include "shared_types.h"
#include "set.h"

namespace handy {
namespace c {
namespace {

using ::testing::TestWithParam;
using ::testing::ValuesIn;

#define CREATE_SET(__set) \
    CSet* __set = nullptr; \
    CSET_CreateSet(&__set, Less<int>); \
    EXPECT_NE(__set, nullptr)

#define DESTROY_SET(__set) \
    CSET_DestroySet(__set); \
    __set = nullptr

const uint32_t MAX_NUMBER = 10;

struct Param {
    int numbers[MAX_NUMBER];
};

const Param unique_params[] = {
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
    { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 },
    { 0, 1, 2, 3, 4, 9, 8, 7, 6, 5 },
    { 9, 8, 7, 6, 5, 0, 1, 2, 3, 4 },
    { 0, 9, 1, 8, 2, 7, 3, 6, 4, 5 },
    { 2, 3, 8, 5, 1, 0, 9, 7, 6, 4 },
    { 6, 5, 0, 1, 2, 4, 8, 7, 9, 3 },
};

const Param equal_params[] = {
    { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4 },
    { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
    { 9, 8, 8, 7, 7, 7, 6, 6, 6, 6 },
    { 1, 2, 2, 3, 3, 9, 8, 8, 7, 7 },
    { 0, 4, 4, 3, 2, 2, 2, 8, 8, 9 },
    { 5, 6, 9, 9, 0, 0, 3, 2, 5, 9 }
};

template<typename T>
bool Less(CReferencePtr lhs, CReferencePtr rhs)
{
    T* lhs_ = reinterpret_cast<T*>(lhs);
    T* rhs_ = reinterpret_cast<T*>(rhs);

    return (*lhs_ < *rhs_);
}

class CSetTestUnique : public TestWithParam<struct Param> {};
class CSetTestEqual : public TestWithParam<struct Param> {};

template <typename T>
static void traverse(CSet* set)
{
    for (CSetIterator it = CSET_Begin(set); it != CSET_End(set); CSET_Forward(&it)) {
        CReferencePtr ref = CSET_Reference(it);
        T* data = reinterpret_cast<T*>(ref);
        printf("%d ", *data);
    }
    printf("\n");
}

TEST(CSetTest, CreateDestroy)
{
    CSet* set = nullptr;
    CSet* ret = CSET_CreateSet(&set, Less<int>);
    EXPECT_EQ(ret, set);
    EXPECT_NE(set, nullptr);
    EXPECT_TRUE(CSET_Empty(set));
    EXPECT_EQ(CSET_Size(set), 0);
    EXPECT_EQ(CSET_Begin(set), CSET_End(set));

    DESTROY_SET(set);
}

TEST(CSetTest, Clear)
{
    const int numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    CREATE_SET(set);
    ARRAY_FOREACH(numbers, i) {
        CREATE_DATA(num, int, numbers[i]);
        CSET_Insert(set, num);
    }

    EXPECT_FALSE(CSET_Empty(set));
    EXPECT_EQ(CSET_Size(set), ARRAY_LENGTH(numbers));
    CSET_Clear(set);
    EXPECT_TRUE(CSET_Empty(set));
    EXPECT_EQ(CSET_Size(set), 0);

    DESTROY_SET(set);
}

TEST_P(CSetTestUnique, InsertErase)
{
    Param param = GetParam();
    CREATE_SET(set);

    ARRAY_FOREACH(param.numbers, i) {
        CREATE_DATA(num, int, param.numbers[i]);
        CSetIterator iter = CSET_Insert(set, num);
        EXPECT_FALSE(CSET_Empty(set));
        EXPECT_EQ(CSET_Size(set), i + 1);
        CSetIterator found = CSET_Find(set, &param.numbers[i]);
        EXPECT_EQ(iter, found);
        int* number_found = reinterpret_cast<int*>(CSET_Reference(found));
        EXPECT_EQ(param.numbers[i], *number_found);
    }

    int* prev = NULL;
    for (CSetIterator it = CSET_Begin(set); it != CSET_End(set); CSET_Forward(&it)) {
        if (it == CSET_Begin(set)) {
            prev = reinterpret_cast<int*>(CSET_Reference(it));
        }
        else {
            int* current = reinterpret_cast<int*>(CSET_Reference(it));
            EXPECT_TRUE(*prev < *current);
            prev = current;
        }
    }

    DESTROY_SET(set);
}

TEST_P(CSetTestEqual, InsertErase)
{
    Param param = GetParam();
    CREATE_SET(set);

    ARRAY_FOREACH(param.numbers, i) {
        CREATE_DATA(num, int, param.numbers[i]);
        size_t size = CSET_Size(set);
        CSET_Insert(set, num);
        EXPECT_FALSE(CSET_Empty(set));
        EXPECT_TRUE(CSET_Size(set) == (size + 1) || CSET_Size(set) == size);
        CSetIterator found = CSET_Find(set, &param.numbers[i]);
        EXPECT_NE(CSET_End(set), found);
        int* number_found = reinterpret_cast<int*>(CSET_Reference(found));
        EXPECT_EQ(param.numbers[i], *number_found);
    }

    int* prev = NULL;
    for (CSetIterator it = CSET_Begin(set); it != CSET_End(set); CSET_Forward(&it)) {
        //printf("%d ", *(reinterpret_cast<int*>(CSET_Reference(it))));
        if (it == CSET_Begin(set)) {
            prev = reinterpret_cast<int*>(CSET_Reference(it));
        }
        else {
            int* current = reinterpret_cast<int*>(CSET_Reference(it));
            EXPECT_TRUE(*prev <= *current);
            prev = current;
        }
    }
    //printf("\n");

    DESTROY_SET(set);
}

INSTANTIATE_TEST_CASE_P(CSetTest, CSetTestUnique, ValuesIn(unique_params));
INSTANTIATE_TEST_CASE_P(CSetTest, CSetTestEqual, ValuesIn(equal_params));

} // namespace
} // namespace c
} // namespace handy
