
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include "container_helper.hpp"

namespace handy {
namespace {

TEST(ContainerHelperTest, PrintElements)
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }

    print_elements(v, std::cout);
}

TEST(ContainerHelperTest, SeqEraseFirst)
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }

    for (int i = 0; i < 10; ++i) {
        erase_first(v, i);
    }

    EXPECT_TRUE(v.size() == 0);
}

TEST(ContainerHelperTest, MapEraseFirst)
{
    std::map<int, int> m;
    for (int i = 0; i < 10; ++i) {
        m[i] = i;
    }

    for (int i = 0; i < 10; ++i) {
        erase_first(m, i);
    }

    EXPECT_TRUE(m.size() == 0);
}

TEST(ContainerHelperTest, SequenceEraseAll)
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(0);
    }

    erase_all(v, 0);
    EXPECT_TRUE(v.size() == 0);
}

TEST(ContainerHelperTest, MapEraseAll)
{
    std::map<int, int> m;
    for (int i = 0; i < 10; ++i) {
        m[i] = 0;
    }

    erase_all(m, 0);
    EXPECT_TRUE(m.size() == 0);
}

} // namespace
} // namespace handy
