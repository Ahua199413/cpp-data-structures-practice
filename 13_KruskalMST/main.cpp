#include "KruskalMST.hpp"
#include "../TestFramework.h"
#include <vector>
#include <iostream>

// ==========================================================
// 測試套件 1: 核心邏輯測試 (標準連通圖)
// ==========================================================
TEST_SUITE(Kruskal_Core_Logic_Test)
    // 建立一個經典的測試圖
    //     (1)
    //  0 ----- 1
    //  | \     |
    //  |(3) \(2)|(4)
    //  |     \ |
    //  2 ----- 3
    //     (5)
    std::vector<Edge> edges = {
        Edge(0, 1, 1),
        Edge(0, 2, 3),
        Edge(0, 3, 2),
        Edge(1, 3, 4),
        Edge(2, 3, 5)
    };

    KruskalMST::Result result = KruskalMST::findMST(4, edges);

    // 最小生成樹應該包含邊 (0-1, w:1), (0-3, w:2), (0-2, w:3)
    TEST_EQUAL(static_cast<size_t>(3), result.mstEdges.size(), "MST Edge Count");
    TEST_EQUAL(6, result.totalWeight, "MST Total Weight");

    // 驗證是否包含特定的邊
    bool found01 = false;
    bool found03 = false;
    bool found02 = false;

    for (const auto& edge : result.mstEdges) {
        if (edge == Edge(0, 1, 1)) found01 = true;
        if (edge == Edge(0, 3, 2)) found03 = true;
        if (edge == Edge(0, 2, 3)) found02 = true;
    }

    TEST_EQUAL(true, found01, "Contains Edge (0-1, w:1)");
    TEST_EQUAL(true, found03, "Contains Edge (0-3, w:2)");
    TEST_EQUAL(true, found02, "Contains Edge (0-2, w:3)");
END_SUITE

// ==========================================================
// 測試套件 2: 邊界條件 (不連通圖)
// ==========================================================
TEST_SUITE(Kruskal_Disconnected_Graph_Test)
    // 0 --(1)-- 1      2 --(2)-- 3
    std::vector<Edge> edges = {
        Edge(0, 1, 1),
        Edge(2, 3, 2)
    };

    KruskalMST::Result result = KruskalMST::findMST(4, edges);

    // 由於圖是不連通的，會產生最小生成森林，這裡會找出 2 條邊
    TEST_EQUAL(static_cast<size_t>(2), result.mstEdges.size(), "Disconnected Graph Edge Count");
    TEST_EQUAL(3, result.totalWeight, "Disconnected Graph Total Weight");
END_SUITE

void run_all_tests() {
    Kruskal_Core_Logic_Test();
    Kruskal_Disconnected_Graph_Test();
}

int main() {
    run_all_tests();
    print_test_report();
    return (g_tests_failed > 0) ? 1 : 0;
}
