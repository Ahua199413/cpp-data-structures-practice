#include "UnionFind.hpp"
#include "../TestFramework.h"

TEST_SUITE(UnionFind_Core_Logic_Test)
    // 初始化 10 個獨立頂點 (0 到 9)
    UnionFind uf(10);

    TEST_EQUAL(10, uf.getCount(), "Initial component count");

    // 測試未連通狀態
    TEST_EQUAL(false, uf.isConnected(0, 1), "0 and 1 should not be connected");
    TEST_EQUAL(false, uf.isConnected(0, 9), "0 and 9 should not be connected");

    // 測試第一次合併 (0 和 1)
    TEST_EQUAL(true, uf.unionSets(0, 1), "Union 0 and 1");
    TEST_EQUAL(true, uf.isConnected(0, 1), "0 and 1 are now connected");
    TEST_EQUAL(9, uf.getCount(), "Component count after 1 union");

    // 測試重複合併 (不應該重複計算)
    TEST_EQUAL(false, uf.unionSets(0, 1), "Union 0 and 1 again (should return false)");
    TEST_EQUAL(9, uf.getCount(), "Component count remains unchanged");

    // 測試多個合併與傳遞性 (Transitivity)
    uf.unionSets(1, 2);
    uf.unionSets(2, 3);
    TEST_EQUAL(true, uf.isConnected(0, 3), "0 and 3 are connected through chain");
    TEST_EQUAL(7, uf.getCount(), "Component count after chaining");
END_SUITE

TEST_SUITE(UnionFind_Advanced_Rank_Test)
    UnionFind uf(5);

    // 合併 0-1, 2-3
    uf.unionSets(0, 1);
    uf.unionSets(2, 3);
    TEST_EQUAL(3, uf.getCount(), "Count before joining two small trees");

    // 合併兩個高度相同的樹 (0-1 群組 與 2-3 群組)
    uf.unionSets(1, 3);
    TEST_EQUAL(2, uf.getCount(), "Count after joining");
    TEST_EQUAL(true, uf.isConnected(0, 2), "0 and 2 are now connected");
END_SUITE

void run_all_tests() {
    UnionFind_Core_Logic_Test();
    UnionFind_Advanced_Rank_Test();
}

int main() {
    run_all_tests();
    print_test_report();
    return (g_tests_failed == 0) ? 0 : 1;
}
