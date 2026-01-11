#include "Queue.hpp"
#include "../TestFramework.h"
#include <string>

// 輔助函式：將隊列內容轉換成字串 (方便 TEST_EQUAL 比較)
template <typename T>
std::string queue_to_string(Queue<T> q)
{ // 這裡用傳值(copy)，才不會破壞原 Queue
    std::string s = "[";
    while (!q.isEmpty())
    {
        s += std::to_string(q.dequeue());
        if (!q.isEmpty())
            s += ", ";
    }
    s += "]";
    return s;
}
// ==========================================================
TEST_SUITE(Queue_Core_Logic_Test)
Queue<int> q;

q.enqueue(10);
q.enqueue(20);
q.enqueue(30);

TEST_EQUAL(3, q.size(), "Size after 3 enqueues");
TEST_EQUAL(10, q.front(), "Front element should be 10 (FIFO)");

TEST_EQUAL(10, q.dequeue(), "First dequeue should be 10");
TEST_EQUAL(2, q.size(), "Size after 1 dequeue");
TEST_EQUAL(20, q.front(), "New front should be 20");

TEST_EQUAL(std::string("[20, 30]"), queue_to_string(q), "Remaining content check");
END_SUITE

TEST_SUITE(Queue_Edge_Cases_Test)
Queue<int> q;

TEST_EQUAL(true, q.isEmpty(), "New queue is empty");
TEST_EXCEPTION(q.dequeue(), std::out_of_range, "Dequeue from empty queue");
TEST_EXCEPTION(q.front(), std::out_of_range, "Front of empty queue");

q.enqueue(100);
TEST_EQUAL(100, q.dequeue(), "Enqueue and dequeue 100");
TEST_EQUAL(true, q.isEmpty(), "Empty again after dequeue");
END_SUITE

void run_all_tests()
{
    Queue_Core_Logic_Test();
    Queue_Edge_Cases_Test();
}

int main()
{
    run_all_tests();
    print_test_report();
    return (g_tests_failed == 0) ? 0 : 1;
}