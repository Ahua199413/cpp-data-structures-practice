#pragma once
#include "../02_LinkedList/LinkedList.hpp"
#include <stdexcept>

// ==========================================================
// 1. 隊列 (Queue) 類別
// ==========================================================
template <typename T>
class Queue
{
private:
    LinkedList<T> storage_; // 使用鏈結串列作為底層結構

public:
    // 構造函式
    Queue() = default;
    ~Queue() = default;

    // 入隊列 (enqueue)
    void enqueue(const T &value)
    {
        storage_.push_back(value);
    }

    // 出隊列 (dequeue)
    T dequeue()
    {
        if (isEmpty())
        {
            throw std::out_of_range("Queue is empty.");
        }
        return storage_.pop_front();
    }

    // 獲取隊列前端元素 (front)
    const T &front() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("Queue is empty.");
        }
        return storage_.get(0);
    }

    // 取得隊列大小
    size_t size() const
    {
        return storage_.getSize();
    }
    // 檢查是否為空
    bool isEmpty() const
    {
        return storage_.isEmpty();
    }
};