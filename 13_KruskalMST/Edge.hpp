#pragma once
#include <iostream>

struct Edge {
    int u;
    int v;
    int weight;

    Edge() : u(0), v(0), weight(0) {}
    Edge(int u_, int v_, int weight_) : u(u_), v(v_), weight(weight_) {}

    // 實作小於運算子，供 BinaryHeap::heapSort 使用 (會由小到大排序)
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }

    // 實作大於運算子，預防未來使用 Min-Heap 的需求
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }

    // 實作等於運算子，方便測試時使用 TEST_EQUAL
    bool operator==(const Edge& other) const {
        return ((u == other.u && v == other.v) || (u == other.v && v == other.u)) &&
               weight == other.weight;
    }

    // 友元函式：讓 Edge 可以被 std::cout 列印出來，方便 TestFramework 顯示 [FAIL] 的資訊
    friend std::ostream& operator<<(std::ostream& os, const Edge& edge) {
        os << "(" << edge.u << "-" << edge.v << ", w:" << edge.weight << ")";
        return os;
    }
};
