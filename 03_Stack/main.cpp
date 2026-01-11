#include "Stack.hpp"
#include "../TestFramework.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

// 輔助函式：將堆疊內容轉換成字串 (方便 TEST_EQUAL 比較)
template <typename T>
std::string stack_to_string(const Stack<T> &stack)
{
    // 為了不破壞原始堆疊，這裡創建一個副本進行遍歷
    Stack<T> temp_stack = stack;
    std::string s = "";
    std::vector<T> elements;

    while (!temp_stack.isEmpty())
    {
        elements.push_back(temp_stack.pop());
    }
    std::reverse(elements.begin(), elements.end());

    for (size_t i = 0; i < elements.size(); i++)
    {
        s += std::to_string(elements[i]);
        if (i != elements.size() - 1)
        {
            s += " -> ";
        }
    }
    return s;
}

// ==========================================================
// 測試套件 1: 核心邏輯 (LIFO)
// ==========================================================
TEST_SUITE(Stack_Core_Logic_Test)
Stack<int> s;

// 測試 push
s.push(10);
s.push(20);
s.push(30); // Stack: 10(底) -> 20 -> 30(頂)

TEST_EQUAL(3, s.size(), "Initial size after pushes");
TEST_EQUAL(30, s.top(), "Top element (LIFO check)");
TEST_EQUAL(std::string("10 -> 20 -> 30"), stack_to_string(s), "Stack content check");

// 測試 pop
TEST_EQUAL(30, s.pop(), "Pop 1st element (should be 30)");
TEST_EQUAL(2, s.size(), "Size after 1 pop");
TEST_EQUAL(20, s.top(), "Top after 1 pop (LIFO)");

TEST_EQUAL(20, s.pop(), "Pop 2nd element (should be 20)");
TEST_EQUAL(1, s.size(), "Size after 2 pops");
TEST_EQUAL(10, s.top(), "Top after 2 pops");
END_SUITE

// ==========================================================
// 測試套件 2: 邊界與異常
// ==========================================================
TEST_SUITE(Stack_Edge_Cases_Test)
Stack<int> s;

// 測試空狀態
TEST_EQUAL(true, s.isEmpty(), "New stack is empty");

// 測試從空堆疊 pop
TEST_EXCEPTION(s.pop(), std::out_of_range, "Pop from empty stack");

// 測試從空堆疊 top
TEST_EXCEPTION(s.top(), std::out_of_range, "Top from empty stack");

// 測試單一元素堆疊
s.push(42);
TEST_EQUAL(42, s.top(), "Top with single element");
TEST_EQUAL(42, s.pop(), "Pop single element");
TEST_EQUAL(true, s.isEmpty(), "Stack should be empty after popping the only element");
END_SUITE

// ==========================================================
// 測試套件 3: 資源管理 (深層複製)
// ==========================================================
TEST_SUITE(Stack_Resource_Management_Test)
Stack<int> original;
original.push(1);
original.push(2);

// 測試複製構造函式 (Copy Constructor)
Stack<int> copy = original;

original.pop(); // 修改原始堆疊

TEST_EQUAL(1, original.size(), "Original size after pop");
TEST_EQUAL(2, copy.size(), "Copy size should remain unchanged");
TEST_EQUAL(2, copy.top(), "Copy top should remain unchanged");

// 測試複製賦值運算符 (Copy Assignment)
Stack<int> assigned;
assigned.push(99);
assigned = copy;
copy.pop(); // 改變來源棧 (Copy: 1)

TEST_EQUAL(1, copy.size(), "Source size after its pop");
TEST_EQUAL(2, assigned.size(), "Assigned size must remain 2");
TEST_EQUAL(2, assigned.top(), "Assigned top must remain 2 (Copy Assignment check)");
END_SUITE

void run_all_tests()
{
    Stack_Core_Logic_Test();
    Stack_Edge_Cases_Test();
    Stack_Resource_Management_Test();
}

int main()
{
    run_all_tests();
    print_test_report();
    return (g_tests_failed == 0) ? 0 : 1;
}