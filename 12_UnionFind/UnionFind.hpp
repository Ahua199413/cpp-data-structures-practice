#pragma once
#include <vector>
#include <numeric> // for std::iota
#include <stdexcept>

class UnionFind {
private:
    std::vector<int> parent_;   // 記錄每個節點的父節點
    std::vector<int> rank_;     // 記錄每個群組的樹高 (Rank)
    int count_;                 // 記錄圖中獨立群組 (連通分支) 的數量

public:
    // 建構子：初始化 V 個頂點，每個頂點一開始都是自己的老大
    UnionFind(int n) : parent_(n), rank_(n, 0), count_(n) {
        // 使用 std::iota 將陣列初始化為 0, 1, 2, ..., n-1
        std::iota(parent_.begin(), parent_.end(), 0);
    }

    // 核心方法 1：尋找頂點 i 的根節點 (老大)
    // 包含神級優化：路徑壓縮 (Path Compression)
    int find(int i) {
        if (i < 0 || i >= parent_.size())
            throw std::out_of_range("Index out of range.");

        // 如果我自己不是老大，就去問我的老大是誰
        // 在回傳的同時，把我的老大直接連到我這裡(壓縮)
        if (i != parent_[i]) {
            parent_[i] = find(parent_[i]);
        }
        return parent_[i];
    }

    // 取得目前群組（連通分支）的總數
    int getCount() const {
        return count_;
    }

    // 檢查 p 和 q 是否屬於同一個群組
    bool isConnected(int p, int q) {
        return find(p) == find(q);
    }

    // 核心方法 2：合併 p 和 q 所在的兩個群組
    // 回傳值: true 代表成功合併 (原先屬於不同群組)
    //        false 代表它們本來就已經在同一個群組了
    bool unionSets(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);

        if (rootP == rootQ) {
            return false;
        }

        // 按秩合併 (Union by Rank)
        if (rank_[rootP] < rank_[rootQ]) {
            parent_[rootP] = rootQ;
        }
        else if (rank_[rootP] > rank_[rootQ]) {
            parent_[rootQ] = rootP;
        }
        else {
            // 兩棵樹一樣高，任選一個 (例如讓 Q 認 P 當老大)
            parent_[rootQ] = rootP;
            // 由於 Q 認了 P，P 樹的高度會增加 1
            rank_[rootP]++;
        }

        // 每成功合併一次，圖中的獨立群組數量就少 1
        count_--;
        return true;
    }
};