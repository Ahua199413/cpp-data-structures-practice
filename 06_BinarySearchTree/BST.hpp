#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm> // for std::swap

// ==========================================================
// 1. 二元搜尋樹節點 (BSTNode) 結構
// ==========================================================
template <typename T>
struct BSTNode
{
    T data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(T val) : data(val), left(nullptr), right(nullptr) {}
}

// ==========================================================
// 2. 二元搜尋樹 (BST) 類別
// ==========================================================
template <typename T>
class BST
{
private:
    BSTNode<T> *root;
    size_t size_;
    // ------------------------------------------------------
    // 內部遞迴輔助函式 (Helper Functions)
    // ------------------------------------------------------

    // 遞迴複製整棵樹
    BSTNode<T> *copy_helper(BSTNode<T> *node) 
    {
        if(node == nullptr)
            return nullptr;

        BSTNode<T> *newNode = new BSTNode<T>(node->data);
        newNode->left = copy_helper(node->left);
        newNode->right = copy_helper(node->right);
        return newNode; 
    }
        

    // 遞迴清理/釋放所有節點
    void clear_helper(BSTNode<T> *node)
    {
        if(node == nullptr)
            return;

        clear_helper(node->left);
        clear_helper(node->right);
        delete node;
    }

    // 遞迴插入節點
    BSTNode<T> *insert_helper(BSTNode<T> *node, T value, bool &inserted)
    {
        if(node == nullptr)
        {
            inserted = true;
            return new BSTNode<T>(value);
        }
        if(value < node->data)
        {
            node->left = insert_helper(node->left, value, inserted);
        }
        else if(value > node->data)
        {
            node->right = insert_helper(node->right, value, inserted);
        }
        else
        {
            // 值已存在，BST 通常不允許重複值
            inserted = false;
        }
        return node;
    }

    // 遞迴搜尋值
    bool search_helper(BSTNode<T> *node, T value) const
    {
        if(node == nullptr)
            return false;
        if(value == node->data)
            return true;
        if(value < node->data)
            return search_helper(node->left, value);
        return search_helper(node->right, value);
    }

    // 尋找給定子樹的最小值節點 (用於刪除操作中的替代)
    BSTNode<T> *find_min(BSTNode<T> *node) const
    {
        if(node == nullptr)
            return nullptr;
        while(node->left != nullptr)
            node = node->left;
        return node;
    }

    // 遞迴刪除節點
    BSTNode<T> *remove_helper(BSTNode<T> *node, T value, bool &removed)
    {
        if(node == nullptr)
        {
            removed = false;
            return nullptr;
        }
        if(value < node->data)
        {
            node->left = remove_helper(node->left, value, removed);
        }
        else if(value > node->data)
        {
            node->right = remove_helper(node->right, value, removed);
        }
        else
        {
            // 找到要刪除的節點了！
            removed = true;
            // 情況 1 & 2: 沒有子節點，或只有單一子節點
            if(node->left == nullptr)
            {
                BSTNode<T> *temp = node->right;
                delete node;
                return temp;
            }
            else if(node->right == nullptr)
            {
                BSTNode<T> *temp = node->left;
                delete node;
                return temp;
            }
            // 情況 3: 有兩個子節點
            // 找出右子樹中的最小值節點 (Inorder Successor) 來替代
            BSTNode<T> *temp = find_min(node->right);
            node->data = temp->data;
            // 在右子樹中刪除該替代節點
            bool dummy = false;
            node->right = remove_helper(node->right, temp->data, dummy);
        }
        return node;
    }
    // 遞迴中序走訪 (Inorder: 左 -> 根 -> 右) - 結果會是遞增排序的
    void inorder_helper(BSTNode<T> *node, std::vector<T> &result) const
    {
        if(node == nullptr)
            return;
        inorder_helper(node->left, result);
        result.push_back(node->data);
        inorder_helper(node->right, result);
    }

    // 遞迴前序走訪 (Preorder: 根 -> 左 -> 右)
    void preorder_helper(BSTNode<T> *node, std::vector<T> &result) const
    {
        if(node == nullptr)
            return;
        result.push_back(node->data);
        preorder_helper(node->left, result);
        preorder_helper(node->right, result);
    }
    // 遞迴後序走訪 (Postorder: 左 -> 右 -> 根)
    void postorder_helper(BSTNode<T> *node, std::vector<T> &result) 
    {
        if(node == nullptr)
            return;
        postorder_helper(node->left, result);
        postorder_helper(node->right, result);
        result.push_back(node->data);
    }
public:
    // 構造函式
    BST() : root_(nullptr), size_(0) {}

    // 析構函式
    ~BST()
    {
        clear();
    }

    // 複製構造函式 (Deep Copy)
    BST(const BST &other) : root_(nullptr), size_(0)
    {
        root_ = copy_helper(other.root_);
        size_ = other.size_;
    }

    // 複製賦值運算符 (Copy-and-Swap idiom)
    BST &operator=(const BST &other)
    {
        if (this != &other)
        {
            BST temp(other);
            std::swap(root_, temp.root_);
            std::swap(size_, temp.size_);
        }
        return *this;
    }

    // 插入值
    bool insert(T value)
    {
        bool inserted = false;
        root_ = insert_helper(root_, value, inserted);
        if (inserted)
        {
            size_++;
        }
        return inserted;
    }

    // 搜尋值
    bool search(T value) const
    {
        return search_helper(root_, value);
    }

    // 刪除值
    bool remove(T value)
    {
        bool removed = false;
        root_ = remove_helper(root_, value, removed);
        if (removed)
        {
            size_--;
        }
        return removed;
    }

    // 清空樹
    void clear()
    {
        clear_helper(root_);
        root_ = nullptr;
        size_ = 0;
    }

    // 基本屬性方法
    size_t size() const { return size_; }
    bool isEmpty() const { return root_ == nullptr; }

    // 走訪介面 (分回 vector 以利測試比對)
    std::vector<T> inorder() const
    {
        std::vector<T> result;
        inorder_helper(root_, result);
        return result;
    }

    std::vector<T> preorder() const
    {
        std::vector<T> result;
        preorder_helper(root_, result);
        return result;
    }

    std::vector<T> postorder() const
    {
        std::vector<T> result;
        postorder_helper(root_, result);
        return result;
    }
};
