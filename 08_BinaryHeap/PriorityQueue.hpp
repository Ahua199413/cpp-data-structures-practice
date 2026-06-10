#pragma once
#include "BinaryHeap.hpp"

template <typename T, typename Compare = std::less<T>>
class PriorityQueue{
private:
    BinaryHeap<T, Compare> heap_;
public:
    PriorityQueue() = default;
    
    void push(const T& val) {
        heap_.insert(val);
    }
    
    void pop() {
        heap_.extractMax();
    }

    const T& top() const {
        return heap_.peek();
    }

    size_t size() const {
        return heap_.size();
    }

    bool empty() const {
        return heap_.isEmpty();
    }
};