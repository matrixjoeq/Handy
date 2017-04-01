
#include <gtest/gtest.h>
#include <iostream>
#include "print_elements.h"
#include "vector_helper.h"

namespace handy {
namespace {

TEST(PrintElementsTest, Print)
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }

    print_elements(v, std::cout);
}

TEST(VectorHelperTest, EraseFirst)
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

TEST(VectorHelperTest, EraseAll)
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(0);
    }

    erase_all(v, 0);
    EXPECT_TRUE(v.size() == 0);
}

} // namespace
} // namespace handy
