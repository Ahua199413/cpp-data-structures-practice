#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "../04_Queue/Queue.hpp"


class Graph {
private:
    int numVertices_;                       // 頂點的總數
    std::vector<std::list<int>> adjLists_;   // 鄰接串列 (使用 list 方便頻繁插入)

    void DFSUtil(int v, std::vector<bool>& visited, std::vector<int>& result) const{
        // 標記目前節點為已走訪
        visited[v] = true;
        // 將目前節點存入結果向量中
        result.push_back(v);
        for (int neighbor : adjLists_[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited, result);
            }
        }
    }
public:
    // 建構子：初始化指定頂點數量的圖
    Graph(int vertices) : numVertices_(vertices), adjLists_(vertices) {}

    // 新增邊 (Edge)
    // u: 起點, v: 終端點
    // bidirectional: true 為無向圖 (雙向), false 為有向圖 (單向)
    void addEdge(int u, int v, bool bidirectional = true) {
        if (u < 0 || u >= numVertices_ || v < 0 || v >= numVertices_ ) {
            throw std::out_of_range("Vertex index out of bounds");
        }

        // 起點連到終點
        adjLists_[u].push_back(v);
        // 如果是無向圖，終點也要連回起點

        if (bidirectional) {
            adjLists_[v].push_back(u);
        }
    }

    // 取得指定頂點的鄰居列表 (唯讀)
    const std::list<int>& getNeighbors(int u) const {
        if (u < 0 || u >= numVertices_) {
            throw std::out_of_range("Vertex index out of range.");
        }
        return adjLists_[u];
    }

    // 取得頂點總數
    int getNumVertices() const {
        return numVertices_;
    }

    // 列印圖的結構 (Debug 用)
    void printGraph() const {
        for (int i = 0; i < numVertices_; i++) {
            std::cout << "Vertex " << i << ": ";
            for (int neighbor : adjLists_[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }

    // 深度優先搜尋 (DFS)
    // startVertex: 走訪的起點
    // 回傳值: 走訪的順序列表
    std::vector<int> DFS(int startVertex) const {
        if (startVertex < 0 || startVertex >= numVertices_) {
            throw std::out_of_range("Vertex index out of range.");
        }
        std::vector<bool> visited(numVertices_, false);
        std::vector<int> result;
        DFSUtil(startVertex, visited, result);

        return result;
    }

    // 廣度優先搜尋 (BFS)
    // startVertex: 走訪的起點
    // 回傳值: 走訪的順序列表
    std::vector<int> BFS(int startVertex) const {
        if (startVertex < 0 || startVertex >= numVertices_) {
            throw std::out_of_range("Start vertex out of range.");
        }
        
        std::vector<bool> visited(numVertices_, false);
        std::vector<int> result;
        
        // 建立我們在 04 章實作的自訂 Queue
        Queue<int> q;
        q.enqueue(startVertex);
        visited[startVertex] = true;
        
        while (!q.isEmpty()) {
            // 走出隊列並記錄
            int currentVertex = q.dequeue();
            result.push_back(currentVertex);

            // 走訪所有鄰居
            for (int neighbor : adjLists_[currentVertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                        q.enqueue(neighbor);
                }
            }
        }
        return result;
    }
};