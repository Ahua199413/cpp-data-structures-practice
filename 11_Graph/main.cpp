#include "Graph.hpp"
#include "../TestFramework.h"
#include <vector>
#include <string>

// 輔助函式：將 vector<int> 轉為字串便於比對
std::string vector_to_string(const std::vector<int> &vec) {
    std::string s = "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        s += std::to_string(vec[i]);
        if (i != vec.size() - 1) s += ", ";
    }
    s += "]";
    return s;
}

// ==========================================================
// 測試套件 1: 圖的建立與鄰居檢查
// ==========================================================
TEST_SUITE(Graph_Core_Structure_Test)
Graph g(4);
g.addEdge(0, 1);
g.addEdge(0, 2);
g.addEdge(1, 3);

TEST_EQUAL(4, g.getNumVertices(), "Vertex count check");

// 檢查 0 號頂點的鄰居是否為 1 和 2
std::list<int> neighbors = g.getNeighbors(0);
auto it = neighbors.begin();
TEST_EQUAL(1, *it, "First neighbor of 0 is 1");
it++;
TEST_EQUAL(2, *it, "Second neighbor of 0 is 2");
END_SUITE

// ==========================================================
// 測試套件 2: DFS 與 BFS 走訪測試
// ==========================================================
TEST_SUITE(Graph_Traversal_Test)
/*
    我們建立一個如下的無向圖：
       0
      / \
     1   2
     |   |
     3 - 4
*/
Graph g(5);
g.addEdge(0, 1);
g.addEdge(0, 2);
g.addEdge(1, 3);
g.addEdge(2, 4);
g.addEdge(3, 4);

// 深度優先搜尋 (DFS)
// 從 0 開始，可能走訪順序為: 0 -> 1 -> 3 -> 4 -> 2
std::vector<int> dfs_res = g.DFS(0);
TEST_EQUAL(std::string("[0, 1, 3, 4, 2]"), vector_to_string(dfs_res), "DFS traversal starting from 0");

// 廣度優先搜尋 (BFS)
// 從 0 開始，按照距離擴散順序應為: 0 -> 1 -> 2 -> 3 -> 4
std::vector<int> bfs_res = g.BFS(0);
TEST_EQUAL(std::string("[0, 1, 2, 3, 4]"), vector_to_string(bfs_res), "BFS traversal starting from 0");
END_SUITE

// ==========================================================
// 測試套件 3: 邊界與異常測試
// ==========================================================
TEST_SUITE(Graph_Edge_Cases_Test)
Graph g(3);
g.addEdge(0, 1);

// 測試超出範圍的頂點
TEST_EXCEPTION(g.addEdge(3, 0), std::out_of_range, "Add edge out of range");
TEST_EXCEPTION(g.DFS(5), std::out_of_range, "DFS start out of range");
TEST_EXCEPTION(g.BFS(-1), std::out_of_range, "BFS start out of range");
END_SUITE

void run_all_tests() {
    Graph_Core_Structure_Test();
    Graph_Traversal_Test();
    Graph_Edge_Cases_Test();
}

int main() {
    run_all_tests();
    print_test_report();
    return (g_tests_failed == 0) ? 0 : 1;
}
