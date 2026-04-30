#include "DynamicArray.hpp"
#include "../TestFramework.h"
#include <stdexcept>

TEST_SUITE(DynamicArray_Core_Logic_Test)
DynamicArray arr;

arr.push_back(10);
arr.push_back(20);
arr.push_back(30);

TEST_EQUAL(3, arr.size(), "Size after 3 pushes");
TEST_EQUAL(10, arr.get(0), "First element check");
TEST_EQUAL(30, arr.get(2), "Last element check");

arr.set(1, 99);
TEST_EQUAL(99, arr.get(1), "Set updates value");

arr.pop_back();
TEST_EQUAL(2, arr.size(), "Size after pop_back");
TEST_EQUAL(99, arr.get(1), "Remaining last element check");
END_SUITE

TEST_SUITE(DynamicArray_Edge_Cases_Test)
DynamicArray arr;

TEST_EQUAL(0, arr.size(), "New array size is 0");
TEST_EXCEPTION(arr.pop_back(), std::out_of_range, "Pop from empty array");
TEST_EXCEPTION(arr.get(0), std::out_of_range, "Get from empty array");

arr.push_back(42);
TEST_EQUAL(42, arr.get(0), "Single element access");
TEST_EXCEPTION(arr.get(1), std::out_of_range, "Get out of range");
TEST_EXCEPTION(arr.set(1, 7), std::out_of_range, "Set out of range");
END_SUITE

TEST_SUITE(DynamicArray_Resize_Test)
DynamicArray arr;

for (int i = 0; i < 20; ++i)
{
    arr.push_back(i * 3);
}

TEST_EQUAL(20, arr.size(), "Size after multiple pushes");
TEST_EQUAL(0, arr.get(0), "First value after resize");
TEST_EQUAL(57, arr.get(19), "Last value after resize");
END_SUITE

void run_all_tests()
{
    DynamicArray_Core_Logic_Test();
    DynamicArray_Edge_Cases_Test();
    DynamicArray_Resize_Test();
}

int main()
{
    run_all_tests();
    print_test_report();
    return (g_tests_failed == 0) ? 0 : 1;
}
