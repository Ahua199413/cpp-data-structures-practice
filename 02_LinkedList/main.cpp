#include "LinkedList.hpp"     // 包含您的鏈結串列實現
#include "../TestFramework.h" // 包含單元測試框架
#include <iostream>
#include <stdexcept>
#include <string>

// 輔助函式：將鏈結串列內容轉換成字串 (方便 TEST_EQUAL 比較)
template <typename T>
std::string list_to_string(const LinkedList<T> &list)
{
    std::string s = "";
    for (size_t i = 0; i < list.getSize(); i++)
    {
        s += std::to_string(list.get(i));
        if (i != list.getSize() - 1)
        {
            s += " -> ";
        }
    }
    return s;
}

// ==========================================================
// 測試套件 1: 核心邏輯 (頭部操作)
// ==========================================================
TEST_SUITE(LinkedList_Core_Logic_Test)
LinkedList<int> ll;

// 測試 push_front
ll.push_front(10);
ll.push_front(20);
ll.push_front(30); // List: 30 -> 20 -> 10
TEST_EQUAL(3, ll.getSize(), "Initial size after pushes");
TEST_EQUAL(30, ll.get(0), "First element check");
TEST_EQUAL(std::string("30 -> 20 -> 10"), list_to_string(ll), "List content check");

// 測試 pop_front
TEST_EQUAL(30, ll.pop_front(), "Pop 1st element (should be 30)");
TEST_EQUAL(2, ll.getSize(), "Size after 1 pop");
TEST_EQUAL(20, ll.get(0), "New head after 1 pop");

TEST_EQUAL(20, ll.pop_front(), "Pop 2nd element (should be 20)");
TEST_EQUAL(1, ll.getSize(), "Size after 2 pops");
TEST_EQUAL(10, ll.get(0), "Remaining element check");
END_SUITE

// ==========================================================
// 測試套件 2: 邊界情況
// ==========================================================
TEST_SUITE(LinkedList_Edge_Cases_Test)
LinkedList<int> ll;

// 測試空狀態
TEST_EQUAL(true, ll.isEmpty(), "New list is empty");

// 測試從空串列 pop_front
TEST_EXCEPTION(ll.pop_front(), std::out_of_range, "Pop from empty list");

// 測試從空串列 get
TEST_EXCEPTION(ll.get(0), std::out_of_range, "Get from empty list");

// 測試單一元素串列
ll.push_front(42);
TEST_EQUAL(42, ll.get(0), "Get with single element");
TEST_EQUAL(42, ll.pop_front(), "Pop single element");
TEST_EQUAL(true, ll.isEmpty(), "List should be empty after popping the only element");
END_SUITE

// ==========================================================
// 測試套件 3: 資源管理 (深層複製)
// ==========================================================
TEST_SUITE(LinkedList_Resource_Management_Test)
LinkedList<int> original;
original.push_front(1);
original.push_front(2); // [2 -> 1]

// 測試複製構造函式 (Copy Constructor)
LinkedList<int> copy(original);
original.pop_front(); // 修改原始串列
TEST_EQUAL(1, original.getSize(), "Original size after pop");
TEST_EQUAL(2, copy.getSize(), "Copy list size check");
TEST_EQUAL(2, copy.get(0), "Copy list first element check");

// 測試複製賦值運算符 (Copy Assignment)
LinkedList<int> assigned;
assigned.push_front(99);
assigned = copy;  // assigned 變成 [2 -> 1]
copy.pop_front(); // 修改 copy 串列 [1]

TEST_EQUAL(1, copy.getSize(), "Source size after its pop");
TEST_EQUAL(2, assigned.getSize(), "Assigned size must remain 2");
TEST_EQUAL(2, assigned.get(0), "Assigned data must remain 2 (Copy-and-Swap check)");
END_SUITE

// ==========================================================
void run_all_tests()
{
    LinkedList_Core_Logic_Test();
    LinkedList_Edge_Cases_Test();
    LinkedList_Resource_Management_Test();
}

int main()
{
    run_all_tests();
    print_test_report();
    return (g_tests_failed == 0) ? 0 : 1;
}
