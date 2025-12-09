#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm> // for std::swap
#include <vector>    // 為了實現深層複製時的輔助反轉

// ==========================================================
// 1. 節點 (Node) 結構
// ==========================================================
template <typename T>
struct StackNode
{
    T data;
    StackNode<T> *next;

    StackNode(T val) : data(val), next(nullptr) {}
};

// ==========================================================
// 2. 堆疊 (Stack) 類別
// ==========================================================
template <typename T>
class Stack
{
private:
    StackNode<T> *topPtr_; // 相當於鏈結串列的 head_
    size_t size_;

    // 內部輔助函式：清理所有節點
    void clear_internal() {
        StackNode<T>* current = topPtr_;
        while (current != nullptr) {
            StackNode<T>* next_node = current->next;
            delete current;
            current = next_node;
        }
        topPtr_ = nullptr;
        size_ = 0;
    }

public:
    // 構造函式
    Stack() : topPtr_(nullptr), size_(0) {}

    // 析構函式
    ~Stack() {
        clear_internal();
    }

    // 複製構造函式 (Deep Copy)
    Stack(const Stack& other) : topPtr_(nullptr), size_(0) {
        if (other.topPtr_ == nullptr) return;

        // 堆疊的深層複製較複雜，需要先將來源串列反轉，再依序 push 才能保持 LIFO 順序
        std::vector<T> elements;
        StackNode<T>* current_other = other.topPtr_;
        while (current_other != nullptr) {
            elements.push_back(current_other->data);
            current_other = current_other->next;
        }
        
        // 由於我們是從 topPtr_ 遍歷的，元素已經是 LIFO 順序 (最新->最舊)
        // 現在我們需要以 FIFO 順序 (最舊->最新) 重新 push 到新堆疊中，才能正確複製
        std::reverse(elements.begin(), elements.end());

        for (const T& val : elements) {
            push(val); 
        }
    }

    // 複製賦值運算符 (Copy-and-Swap idiom)
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            // 複製: 使用 Copy Constructor 建立一個副本
            Stack temp = other; 
            // 交換: 交換資源 (指標)
            std::swap(topPtr_, temp.topPtr_);
            std::swap(size_, temp.size_);
        }
        return *this;
    }

    void push(T value) {
        StackNode<T>* newNode = new StackNode<T> (value);
        newNode->next = topPtr_;
        topPtr_ = newNode;
        size_++;
    }

    T pop() {
        if (topPtr_ == nullptr) {
            throw std::out_of_range("Error: Stack is empty. Cannot pop.");
        }
        StackNode<T>* temp = topPtr_;
        T data = topPtr_->data;
        topPtr_ = topPtr_->next;
        delete temp;
        size_--;
        return data;
    }

    T top() const {
        if (topPtr_ == nullptr) {
            throw std::out_of_range("Error: Stack is empty. No top element.");
        }
        return topPtr_->data;
    }

    bool isEmpty() const { return topPtr_ == nullptr; }
    size_t size() const { return size_;}
};