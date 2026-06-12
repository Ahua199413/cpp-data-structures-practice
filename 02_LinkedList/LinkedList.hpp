#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm> // for std::swap

// ==========================================================
// 1. 節點 (SinglyNode) 結構
// ==========================================================
template <typename T>
struct SinglyNode
{
    T data;
    SinglyNode<T> *next;

    SinglyNode(T val) : data(val), next(nullptr) {}
};

// ==========================================================
// 2. 鏈結串列 (LinkedList) 類別
// ==========================================================
template <typename T>
class LinkedList
{
private:
    SinglyNode<T> *head_;
    SinglyNode<T> *tail_;
    size_t size_;

    // 內部輔助函式：清理所有節點
    void clear_internal()
    {
        SinglyNode<T> *current = head_;
        while (current != nullptr)
        {
            SinglyNode<T> *next_node = current->next;
            delete current;
            current = next_node;
        }
        head_ = nullptr;
        size_ = 0;
    }

public:
    // 構造函式
    LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

    // 析構函式
    ~LinkedList()
    {
        clear_internal();
    }

    LinkedList(const LinkedList &other) : head_(nullptr), tail_(nullptr), size_(0)
    {
        try
        {
            for (SinglyNode<T> *curr = other.head_; curr != nullptr; curr = curr->next)
            {
                push_back(curr->data);
            }
        }
        catch (...)
        {
            clear_internal();
            throw;
        }
    }

    // 複製賦值運算符 (Copy-and-Swap idiom)
    LinkedList &operator=(const LinkedList &other)
    {
        if (this != &other)
        {
            // 1. 建立副本
            LinkedList temp(other);
            // 2. 交換內容
            std::swap(this->head_, temp.head_);
            std::swap(this->tail_, temp.tail_);
            std::swap(this->size_, temp.size_);
        }
        return *this;
    }
    // ==========================================================
    // core operations (push_front, push_back, pop_front, get, isEmpty, getSize)
    // ==========================================================

    // insert at the front O(1)
    void push_front(const T &data)
    {
        SinglyNode<T> *newNode = new SinglyNode<T>(data);
        if (isEmpty())
        {
            head_ = newNode;
            tail_ = head_;
        }
        else
        {
            newNode->next = head_;
            head_ = newNode;
        }
        size_++;
    }

    // insert at the back O(1)
    void push_back(const T &data)
    {
        SinglyNode<T> *newNode = new SinglyNode<T>(data);
        if (isEmpty())
        {
            head_ = newNode;
            tail_ = newNode;
        }
        else
        {
            tail_->next = newNode;
            tail_ = newNode;
        }
        size_++;
    }

    // remove from the front O(1)
    T pop_front()
    {
        if (isEmpty())
            throw std::out_of_range("List is empty.");

        SinglyNode<T> *temp = head_;
        T val = head_->data;
        head_ = head_->next;

        delete temp;
        size_--;

        if (isEmpty())
            tail_ = nullptr;

        return val;
    }

    // remove from the back O(n)
    T pop_back()
    {
        if (isEmpty())
            throw std::out_of_range("List is empty.");

        T val = tail_->data;
        SinglyNode<T> *oldTail = tail_;

        if (size_ == 1)
        {
            head_ = nullptr;
            tail_ = nullptr;
        }
        else
        {
            SinglyNode<T> *current = head_;
            while (current->next != tail_)
            {
                current = current->next;
            }
            tail_ = current;
            tail_->next = nullptr;
        }

        delete oldTail;
        size_--;
        return val;
    }
    // get element at index O(n)
    const T &get(size_t index) const
    {
        if (index >= size_)
            throw std::out_of_range("Index out of range.");

        SinglyNode<T> *current = head_;
        for (size_t i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->data;
    }

    bool isEmpty() const { return head_ == nullptr; }

    size_t getSize() const { return size_; }
};