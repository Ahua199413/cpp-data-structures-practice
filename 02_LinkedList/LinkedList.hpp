#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm> // for std::swap
// ==========================================================
// 1. 節點 (Node) 結構
// ==========================================================
template <typename T>
struct Node
{
    T data;
    Node<T> *next;

    Node(T val) : data(val), next(nullptr) {}
};

// ==========================================================
// 2. 鏈結串列 (LinkedList) 類別
// ==========================================================
template <typename T>
class LinkedList
{
private:
    Node<T> *head_;
    Node<T> *tail_;
    size_t size_;

    // 內部輔助函式：清理所有節點
    void clear_internal()
    {
        Node<T> *current = head_;
        while (current != nullptr)
        {
            Node<T> *next_node = current->next;
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

    // 複製構造函式 (Deep Copy)
    LinkedList(const LinkedList &other) : head_(nullptr), size_(0)
    {
        if (other.head_ == nullptr)
            return;

        // 1. 複製節點
        head_ = new Node<T>(other.head_->data);
        Node<T> *current_new = head_;
        Node<T> *current_other = other.head_->next;

        // 2. 依序複製其他節點
        while (current_other != nullptr)
        {
            current_new->next = new Node<T>(current_other->data);
            current_new = current_new->next;
            current_other = current_other->next;
        }
        size_ = other.size_;
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
        Node<T> *newNode = new Node<T>(data);
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

    // instert at the back O(n)
    void push_back(const T &data)
    {
        Node<T> *newNode = new Node<T>(data);
        if (isEmpty())
        {
            head_ = newNode;
        }
        else
        {
            Node<T> *current = head_;
            while (current->next)
            {
                current = current->next;
            }
            current->next = newNode;
        }
        size_++;
    }

    // remove from the front O(1)
    T pop_front()
    {
        if (isEmpty())
            throw std::out_of_range("List is empty.");

        Node<T> *temp = head_;
        T val = head_->data;
        head_ = head_->next;

        delete temp;
        size_--;

        if (isEmpty())
            tail_ = nullptr;

        return val;
    }

    // get element at index O(n)
    const T &get(size_t index) const
    {
        if (index >= size_)
            throw std::out_of_range("Index out of range.");

        Node<T> *current = head_;
        for (size_t i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->data;
    }

    bool isEmpty() const { return head_ == nullptr; }

    size_t getSize() const { return size_; }
};