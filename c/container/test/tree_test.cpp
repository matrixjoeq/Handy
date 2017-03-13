
#include <gtest/gtest.h>
#include "shared_types.h"
#include "tree.h"

namespace handy {
namespace c {
namespace {

using ::testing::TestWithParam;
using ::testing::ValuesIn;

#define CREATE_TREE(__tree) \
    CTree* __tree = nullptr; \
    CTREE_CreateTree(&__tree, Less<int>); \
    EXPECT_NE(__tree, nullptr)

#define DESTROY_TREE(__tree) \
    CTREE_DestroyTree(__tree); \
    __tree = nullptr

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
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
    { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 },
    { 0, 1, 2, 3, 4, 9, 8, 7, 6, 5 },
    { 9, 8, 7, 6, 5, 0, 1, 2, 3, 4 },
    { 0, 9, 1, 8, 2, 7, 3, 6, 4, 5 },
    { 2, 3, 8, 5, 1, 0, 9, 7, 6, 4 },
    { 6, 5, 0, 1, 2, 4, 8, 7, 9, 3 },
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

class CTreeTestUnique : public TestWithParam<struct Param> {};
class CTreeTestEqual : public TestWithParam<struct Param> {};

TEST(CTreeTest, CreateDestroy)
{
    CTree* tree = nullptr;
    CTree* ret = CTREE_CreateTree(&tree, Less<int>);
    EXPECT_EQ(ret, tree);
    EXPECT_NE(tree, nullptr);
    EXPECT_TRUE(CTREE_Empty(tree));
    EXPECT_EQ(CTREE_Size(tree), 0);
    EXPECT_EQ(CTREE_Begin(tree), CTREE_End(tree));

    DESTROY_TREE(tree);
}

TEST_P(CTreeTestUnique, InsertErase)
{
    Param param = GetParam();
    CREATE_TREE(tree);

    ARRAY_FOREACH(param.numbers, i) {
        CREATE_DATA(num, int, param.numbers[i]);
        CTREE_InsertUnique(tree, num);
        EXPECT_FALSE(CTREE_Empty(tree));
        EXPECT_EQ(CTREE_Size(tree), i + 1);
        EXPECT_NE(CTREE_End(tree), CTREE_Find(tree, &param.numbers[i]));
    }

    int* prev = NULL;
    for (CTreeNode* it = CTREE_Begin(tree); it != CTREE_End(tree); CTREE_Forward(&it)) {
        if (it == CTREE_Begin(tree)) {
            prev = reinterpret_cast<int*>(CTREE_Reference(it));
        }
        else {
            int* current = reinterpret_cast<int*>(CTREE_Reference(it));
            EXPECT_TRUE(*prev < *current);
            prev = current;
        }
    }

    DESTROY_TREE(tree);
}

TEST_P(CTreeTestEqual, InsertErase)
{
    Param param = GetParam();
    CREATE_TREE(tree);

    ARRAY_FOREACH(param.numbers, i) {
        CREATE_DATA(num, int, param.numbers[i]);
        CTREE_InsertEqual(tree, num);
        EXPECT_FALSE(CTREE_Empty(tree));
        EXPECT_EQ(CTREE_Size(tree), i + 1);
        EXPECT_NE(CTREE_End(tree), CTREE_Find(tree, &param.numbers[i]));
    }

    int* prev = NULL;
    for (CTreeNode* it = CTREE_Begin(tree); it != CTREE_End(tree); CTREE_Forward(&it)) {
        if (it == CTREE_Begin(tree)) {
            prev = reinterpret_cast<int*>(CTREE_Reference(it));
        }
        else {
            int* current = reinterpret_cast<int*>(CTREE_Reference(it));
            EXPECT_TRUE(*prev <= *current);
            prev = current;
        }
    }

    DESTROY_TREE(tree);
}

INSTANTIATE_TEST_CASE_P(CTreeTest, CTreeTestUnique, ValuesIn(unique_params));
INSTANTIATE_TEST_CASE_P(CTreeTest, CTreeTestEqual, ValuesIn(equal_params));

} // namespace
} // namespace c
} // namespace handy
