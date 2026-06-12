#include "Deque.hpp"
#include "../TestFramework.h"
#include <string>

// 輔助函式：將雙端佇列內容轉換成字串 (方便 TEST_EQUAL 比較)
template <typename T>
std::string deque_to_string(Deque<T> dq)
{ // 這裡用傳值(copy)，才不會破壞原 Deque
    std::string s = "[";
    while (!dq.isEmpty())
    {
        s += std::to_string(dq.pop_front());
        if (!dq.isEmpty())
            s += ", ";
    }
    s += "]";
    return s;
}
// ==========================================================

TEST_SUITE(Deque_Mixed_Operations)
Deque<int> dq;

dq.push_back(10);  // [10]
dq.push_front(20); // [20, 10]
dq.push_back(30);  // [20, 10, 30]

TEST_EQUAL(20, dq.front(), "Check front");
TEST_EQUAL(30, dq.back(), "Check back");

TEST_EQUAL(20, dq.pop_front(), "Pop front"); // 剩下 [10, 30]
TEST_EQUAL(30, dq.pop_back(), "Pop back");   // 剩下 [10]
TEST_EQUAL(10, dq.pop_front(), "Pop last");  // 剩下 []

TEST_EQUAL(true, dq.isEmpty(), "Should be empty");
END_SUITE
// ==========================================================
void run_all_tests()
{
    Deque_Mixed_Operations(); // 或是你定義的測試套件名稱
}

int main()
{
    run_all_tests();
    print_test_report();
    return (g_tests_failed == 0) ? 0 : 1;
}