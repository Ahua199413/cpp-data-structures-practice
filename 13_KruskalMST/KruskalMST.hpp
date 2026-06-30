#pragma once
#include <vector>
#include <algorithm>
#include "../12_UnionFind/UnionFind.hpp"
#include "../08_BinaryHeap/BinaryHeap.hpp"
#include "Edge.hpp"

class KruskalMST {
public:
    struct Result {
        std::vector<Edge> mstEdges;
        int totalWeight;
    };

    static Result findMST(int numVertices, std::vector<Edge>& edges) {
        // 1. 檢查頂點數量
        if (numVertices <= 0) {
            return Result{{}, 0};
        }

        // 2. 將邊按照權重從小到大排序
        // 這裡我們利用了之前在第 8 章實作的 BinaryHeap::heapSort！
        BinaryHeap<Edge>::heapSort(edges);

        // 3. 初始化 Union-Find
        UnionFind uf(numVertices);

        Result result{ {}, 0 };

        // 4. 遍歷所有的邊
        for (const auto& edge : edges) {
            // 如果起點與終點尚未連通 (即加入此邊不會形成環)
            if (uf.unionSets(edge.u, edge.v)) {
                // 將邊加入最小生成樹
                result.mstEdges.push_back(edge);
                result.totalWeight += edge.weight;

                // 如果 MST 中的邊數已經達到 V - 1，代表最小生成樹已建立完成
                if (result.mstEdges.size() == static_cast<size_t>(numVertices - 1)) {
                    break;
                }
            }
        }

        return result;
    }
};
