#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm> // for std::swap

// ==========================================================
// 1. 節點 (DoublyNode) 結構
// ==========================================================
template <typename T>
struct DoublyNode
{
    T data;
    DoublyNode<T> *next;
    DoublyNode<T> *prev;

    DoublyNode(T val) : data(val), next(nullptr), prev(nullptr) {}
};

// ==========================================================
// 2. 鏈結串列 (DoublyLinkedList) 類別
// ==========================================================
template <typename T>
class DoublyLinkedList
{
private:
    DoublyNode<T> *head_;
    DoublyNode<T> *tail_;
    size_t size_;

    // 內部輔助函式：清理所有節點
    void clear_internal()
    {
        DoublyNode<T> *current = head_;
        while (current != nullptr)
        {
            DoublyNode<T> *next_node = current->next;
            delete current;
            current = next_node;
        }
        head_ = nullptr;
        size_ = 0;
    }

public:
    // 構造函式
    DoublyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

    // 析構函式
    ~DoublyLinkedList()
    {
        clear_internal();
    }

    // 複製構造函式 (Deep Copy)
    DoublyLinkedList(const DoublyLinkedList &other) : head_(nullptr), tail_(nullptr), size_(0)
    {
        if (other.head_ == nullptr)
            return;

        // 1. 複製第一個節點
        head_ = new DoublyNode<T>(other.head_->data);
        DoublyNode<T> *current_new = head_;
        DoublyNode<T> *current_other = other.head_->next;

        // 2. 依序複製其他節點並建立雙向連結
        while (current_other != nullptr)
        {
            DoublyNode<T> *newNode = new DoublyNode<T>(current_other->data);
            current_new->next = newNode;
            newNode->prev = current_new;
            current_new = newNode;
            current_other = current_other->next;
        }
        tail_ = current_new;
        size_ = other.size_;
    }

    // 複製賦值運算符 (Copy-and-Swap idiom)
    DoublyLinkedList &operator=(const DoublyLinkedList &other)
    {
        if (this != &other)
        {
            // 1. 建立副本
            DoublyLinkedList temp(other);
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
        DoublyNode<T> *newNode = new DoublyNode<T>(data);
        if (isEmpty())
        {
            head_ = newNode;
            tail_ = head_;
        }
        else
        {
            newNode->next = head_;
            head_->prev = newNode;
            head_ = newNode;
        }
        size_++;
    }

    // insert at the back O(1)
    void push_back(const T &data)
    {
        DoublyNode<T> *newNode = new DoublyNode<T>(data);
        if (isEmpty())
        {
            head_ = tail_ = newNode;
        }
        else
        {
            newNode->prev = tail_;
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

        DoublyNode<T> *temp = head_;
        T val = head_->data;
        head_ = head_->next;

        delete temp;
        size_--;

        if (isEmpty())
        {
            tail_ = nullptr;
        }
        else
        {
            head_->prev = nullptr;
        }

        return val;
    }

    // remove from the back O(1)
    T pop_back()
    {
        if (isEmpty())
            throw std::out_of_range("List is empty.");

        T val = tail_->data;
        DoublyNode<T> *oldTail = tail_;

        if (size_ == 1)
        {
            head_ = nullptr;
            tail_ = nullptr;
        }
        else
        {
            tail_ = tail_->prev;
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

        DoublyNode<T> *current = head_;
        for (size_t i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->data;
    }

    bool isEmpty() const { return head_ == nullptr; }

    size_t getSize() const { return size_; }

    // 為了展示雙向性，我們加一個「反向獲取」的邏輯
    const T &get_from_back(size_t index_from_tail) const
    {
        if (index_from_tail >= size_)
            throw std::out_of_range("Index out of bounds");
        DoublyNode<T> *current = tail_;
        for (size_t i = 0; i < index_from_tail; ++i)
        {
            current = current->prev; // 往回走！
        }
        return current->data;
    }
};