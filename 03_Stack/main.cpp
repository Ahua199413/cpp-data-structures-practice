#include "Stack.hpp"
#include "../TestFramework.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

// 輔助函式：將堆疊內容轉換成字串 (方便 TEST_EQUAL 比較)
template <typename T>
std::string stack_to_string(const Stack<T>& stack) {
    // 為了不破壞原始堆疊，這裡創建一個副本進行遍歷
    Stack<T> temp_stack = stack;
    std::string s = "";
    std::vector<T> elements;

    while (!temp_stack.isEmqpty()) {
        elements.push_back(temp_stack.pop());
    }
    std::reverse(elements.begin(), elements.end());

    for (size_t i = 0; i < elements.size(); i++) {
        s += std::to_string(elements[i]);
        if (i != elements.size() - 1) {
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