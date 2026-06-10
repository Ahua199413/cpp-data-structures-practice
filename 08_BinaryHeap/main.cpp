#include "BinaryHeap.hpp"
#include "../TestFramework.h"
#include <stdexcept>

TEST_SUITE(BinaryHeap_Core_Operations)
BinaryHeap<int> heap;

TEST_EQUAL(true, heap.isEmpty(), "New heap is empty");
TEST_EQUAL(0, heap.size(), "New heap size is 0");

heap.insert(10);
TEST_EQUAL(10, heap.peek(), "Peek after inserting 10");
TEST_EQUAL(1, heap.size(), "Size after inserting 10");

heap.insert(20);
TEST_EQUAL(20, heap.peek(), "Peek after inserting 20 (heap property checks)");
TEST_EQUAL(2, heap.size(), "Size is 2");

heap.insert(15);
TEST_EQUAL(20, heap.peek(), "Peek after inserting 15 (should not change max)");
TEST_EQUAL(3, heap.size(), "Size is 3");

heap.insert(40);
TEST_EQUAL(40, heap.peek(), "Peek after inserting 40 (new max)");
TEST_EQUAL(4, heap.size(), "Size is 4");
END_SUITE

TEST_SUITE(BinaryHeap_Extraction_Test)
BinaryHeap<int> heap;
heap.insert(10);
heap.insert(40);
heap.insert(20);
heap.insert(15);
heap.insert(30);

TEST_EQUAL(5, heap.size(), "Initial size is 5");
TEST_EQUAL(40, heap.peek(), "Initial max is 40");

TEST_EQUAL(40, heap.extractMax(), "Extract max (40)");
TEST_EQUAL(30, heap.peek(), "New max is 30");
TEST_EQUAL(4, heap.size(), "Size is 4");

TEST_EQUAL(30, heap.extractMax(), "Extract max (30)");
TEST_EQUAL(20, heap.peek(), "New max is 20");

TEST_EQUAL(20, heap.extractMax(), "Extract max (20)");
TEST_EQUAL(15, heap.peek(), "New max is 15");

TEST_EQUAL(15, heap.extractMax(), "Extract max (15)");
TEST_EQUAL(10, heap.peek(), "New max is 10");

TEST_EQUAL(10, heap.extractMax(), "Extract max (10)");
TEST_EQUAL(true, heap.isEmpty(), "Heap is now empty");
TEST_EQUAL(0, heap.size(), "Heap size is 0");
END_SUITE

TEST_SUITE(BinaryHeap_Edge_Cases)
BinaryHeap<int> heap;

TEST_EXCEPTION(heap.peek(), std::out_of_range, "Peek empty heap throws exception");
TEST_EXCEPTION(heap.extractMax(), std::out_of_range, "Extract from empty heap throws exception");
END_SUITE

TEST_SUITE(BinaryHeap_Deep_Copy_Test)
BinaryHeap<int> original;
original.insert(10);
original.insert(30);
original.insert(20);

// Test Copy Constructor
BinaryHeap<int> copy_constructed(original);
TEST_EQUAL(3, copy_constructed.size(), "Copied heap size check");
TEST_EQUAL(30, copy_constructed.peek(), "Copied heap max check");

copy_constructed.insert(50);
TEST_EQUAL(50, copy_constructed.peek(), "Copied heap new max");
TEST_EQUAL(30, original.peek(), "Original heap max unaffected (Deep Copy)");

// Test Copy Assignment
BinaryHeap<int> copy_assigned;
copy_assigned.insert(5);
copy_assigned = original;
TEST_EQUAL(3, copy_assigned.size(), "Assigned heap size check");
TEST_EQUAL(30, copy_assigned.peek(), "Assigned heap max check");

copy_assigned.insert(100);
TEST_EQUAL(100, copy_assigned.peek(), "Assigned heap new max");
TEST_EQUAL(30, original.peek(), "Original heap max unaffected (Deep Copy Assignment)");
END_SUITE

TEST_SUITE(BinaryHeap_Heapify_Test)
std::vector<int> unsorted = {15, 10, 20, 8, 30, 50, 22};
BinaryHeap<int> heap(unsorted);
TEST_EQUAL(7, heap.size(), "Size of heapified heap");
TEST_EQUAL(50, heap.peek(), "Max element check");
// 依序取出應為遞減排序：50, 30, 22, 20, 15, 10, 8
TEST_EQUAL(50, heap.extractMax(), "Extract 50");
TEST_EQUAL(30, heap.extractMax(), "Extract 30");
TEST_EQUAL(22, heap.extractMax(), "Extract 22");
TEST_EQUAL(20, heap.extractMax(), "Extract 20");
TEST_EQUAL(15, heap.extractMax(), "Extract 15");
TEST_EQUAL(10, heap.extractMax(), "Extract 10");
TEST_EQUAL(8, heap.extractMax(), "Extract 8");
TEST_EQUAL(true, heap.isEmpty(), "Heap should be empty");
END_SUITE

TEST_SUITE(BinaryHeap_Sort_Test)
std::vector<int> data = {40, 10, 30, 15, 50, 20, 5, 25};
BinaryHeap<int>::heapSort(data);
// 排序後應該要是升序 (從小到大)
std::vector<int> expected = {5, 10, 15, 20, 25, 30, 40, 50};
for (size_t i = 0; i < data.size(); ++i) {
    TEST_EQUAL(expected[i], data[i], "Check element index " + std::to_string(i));
}
END_SUITE

TEST_SUITE(MinHeap_Test)
BinaryHeap<int, std::greater<int>> min_heap;
min_heap.insert(30);
min_heap.insert(10);
min_heap.insert(20);

TEST_EQUAL(10, min_heap.peek(), "Min-Heap peek should be 10 (smallest)");
TEST_EQUAL(10, min_heap.extractMax(), "Extract min (10)"); // 注意：為求 API 統一，你可以保留 extractMax 名稱，或者重構為更通用的 extractTop / pop。
TEST_EQUAL(20, min_heap.peek(), "New min is 20");
END_SUITE

TEST_SUITE(PriorityQueue_Test)
PriorityQueue<int> pq; // 預設為最大優先佇列 (Max-Priority Queue)
pq.push(10);
pq.push(30);
pq.push(20);

TEST_EQUAL(30, pq.top(), "Top element check");
pq.pop();
TEST_EQUAL(20, pq.top(), "New top element check");
pq.pop();
TEST_EQUAL(10, pq.top(), "Last element check");
pq.pop();
TEST_EQUAL(true, pq.empty(), "PriorityQueue should be empty");
END_SUITE


void run_all_tests() {
    BinaryHeap_Core_Operations();
    BinaryHeap_Extraction_Test();
    BinaryHeap_Edge_Cases();
    BinaryHeap_Deep_Copy_Test();
    BinaryHeap_Heapify_Test();
    BinaryHeap_Sort_Test();
    MinHeap_Test();
    PriorityQueue_Test();
}

int main() {
    run_all_tests();
    print_test_report();
    return (g_tests_failed == 0) ? 0 : 1;
}
