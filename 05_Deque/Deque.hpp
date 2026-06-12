#pragma once
#include "../02_LinkedList/DoublyLinkedList.hpp"
#include <stdexcept>

template <typename T>
class Deque
{
private:
    DoublyLinkedList<T> storage_;

public:
    Deque() = default;
    ~Deque() = default;

    // --- 前端操作 ---
    void push_front(const T &val) { storage_.push_front(val); }
    T pop_front() { return storage_.pop_front(); }
    const T &front() const { return storage_.get(0); }

    // --- 後端操作 ---
    void push_back(const T &val) { storage_.push_back(val); }
    T pop_back() { return storage_.pop_back(); }
    const T &back() const { return storage_.get_from_back(0); }

    // --- 狀態檢查 ---
    bool isEmpty() const { return storage_.isEmpty(); }
    size_t size() const { return storage_.getSize(); }
};