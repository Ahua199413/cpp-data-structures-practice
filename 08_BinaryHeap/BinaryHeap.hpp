#pragma once
#include <vector>
#include <stdexcept>
#include <algorithm> // for std::swap
#include <functional>


template <typename T, typename Compare = std::less<T>>
class BinaryHeap {
private:
    std::vector<T> heap_;
    Compare comp_;

    // 索引計算輔助函式
    inline int parent(int i) const {return (i - 1) / 2;}
    inline int right(int i) const {return 2 * i + 2;}
    inline int left(int i) const {return 2 * i + 1;}
    
    // 上浮操作 (Sift Up)
    void siftUp(int i) {
        // 當前節點不是根節點，且當前節點值大於其父節點值時，持續上浮
        while (i > 0 && comp_(heap_[parent(i)], heap_[i])) {
            std::swap(heap_[i], heap_[parent(i)]);
            i = parent(i);
        }
    }

    // 新增 static 版本的 siftDown，支援自訂 vector 和大小限制
    static void siftDownStatic(std::vector<T>& vec, int i, int heapSize) {
        Compare comp;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int maxIndex = i;
        
        if (l < heapSize && comp(vec[maxIndex], vec[l])) {
            maxIndex = l;
        }
        if (r < heapSize && comp(vec[maxIndex], vec[r])) {
            maxIndex = r;
        }
        if (maxIndex != i) {
            std::swap(vec[i], vec[maxIndex]);
            siftDownStatic(vec, maxIndex, heapSize);
        }
    }
    // 下沉操作 (Sift Down)
    void siftDown(int i) {
        siftDownStatic(heap_, i, heap_.size());
    }
    

public:
    // 构造函式
    BinaryHeap() = default;
    BinaryHeap(const std::vector<T>& values) {
        heap_ = values;
        if (heap_.size() > 1) {
            int last_non_leaf = parent(heap_.size() - 1);       // 略過葉子節點（Leaf Nodes）： 樹的葉子節點沒有子節點，所以對它們執行 siftDown 是完全沒有作用的（會直接返回）。       
            for (int i = last_non_leaf; i >= 0; --i) {          // Heap 中有一半的節點都是葉子節點，如果我們從最後一個非葉子節點開始，可以省去約 50% 的 siftDown 呼叫
                siftDown(i);
            }
        }
    };

    // 原地堆疊排序：時間 O(N log N)，額外空間 O(1)
    static void heapSort(std::vector<T>& vec) {
        int n = vec.size();
        if (n <= 1)    return;

        // 1: 建立 Max Heap (使用 Bottom-up Heapify)
        // 從最後一個有子節點的節點開始下沉
        for (int i = (n / 2) - 1; i >= 0; --i) {
            siftDownStatic(vec, i, n);
        }
        // 2: 依序將最大值交換到陣列尾端，並縮小 Heap 範圍進行下沉
        for (int i = n - 1; i > 0; --i) {
            std::swap(vec[0], vec[i]);
            siftDownStatic(vec, 0, i);
        }
    }
    
    // 插入新元素
    void insert(const T& value) {
        // 1. 將新元素加到向量的末尾
        heap_.push_back(value);
        // 2. 執行上浮操作以恢復堆屬性
        siftUp(heap_.size() - 1);
    }

    // 取得最大值 (查看堆頂元素)
    const T& peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap_[0];
    }
    T extractMax() {
        if (isEmpty()) {
            throw std::out_of_range("Heap is empty");
        }

        T rootValue = heap_[0];
        heap_[0] = heap_.back();
        heap_.pop_back();
        if (!isEmpty()) {
            siftDown(0);
        }
        return rootValue;
    }
    size_t size() const { return heap_.size(); }
    bool isEmpty() const { return heap_.empty(); }

};