#pragma once
#include <iostream>
#include <algorithm> // for std::max, std::swap
#include <vector>
#include "../04_Queue/Queue.hpp"

template <typename T>
struct AVLNode {
    T data;
    AVLNode* left;
    AVLNode* right;
    int height; // 記錄以該節點為根的子樹高度

    AVLNode(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class AVLTree{
private:
    AVLNode<T>* root;
    size_t size_;

    // 遞迴複製整棵樹 (深拷貝)
    AVLNode<T>* copy_helper(AVLNode<T>* node) {
        if (node == nullptr)    return nullptr;
        AVLNode<T>* newNode = new AVLNode<T>(node->data);
        try {
            newNode->left = copy_helper(node->left);
            newNode->right = copy_helper(node->right);
        } catch (...) {
            clear_helper(newNode->left);
            delete newNode;
            throw;
        }
        newNode->height = node->height;
        return newNode;
    }

    // 遞迴刪除整棵樹 (深層清理)
    void clear_helper(AVLNode<T>* node) {
        if (node == nullptr)    return;
        clear_helper(node->left);
        clear_helper(node->right);
        delete node;
    }

    // 取得節點高度的輔助函式 (安全處理 nullptr)
    int getHeight(AVLNode<T>* node) const {
        return node ? node->height : 0;   // 如果節點存在則回傳其 height，否則回傳 0 (空樹高度為 0)
    }

    // 更新節點高度 (以左右子樹的最大高度 + 1)
    void updateHeight(AVLNode<T>* node) {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    // 取得節點的平衡因子 (Balance Factor)
    int getBalanceFactor(AVLNode<T>* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // 右旋 (Right Rotation)
    // (用於解決 LL 型不平衡)
    //         y                 x
    //        / \              /   \
    //       x   T3   ==>     T1    y
    //      / \                    / \
    //     T1  T2                 T2  T3
    AVLNode<T>* rightRotate(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;

        // 進行旋轉
        x->right = y;
        y->left = T2;   
        
        // 重新計算高度 (必須先算 y，再算 x，因為 y 現在是 x 的子節點)
        // 更新節點高度必須「由底向上」更新（也就是先更新子節點，再更新父節點）。
        updateHeight(y);
        updateHeight(x);

        // 回傳新的根節點
        return x;
    }
        
    // 左旋 (Left Rotation)
    // (用於解決 RR 型不平衡)
    //     x                   y
    //    / \                /   \
    //   T1  y     ==>     x     T3
    //      / \            / \
    //     T2  T3         T1  T2
    AVLNode<T>* leftRotate(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;

        // 進行旋轉
        y->left = x;
        x->right = T2;

        // 更新高度(必須先算 x，再算 y，因為 x 現在是 y 的子節點)
        // 更新節點高度必須「由底向上」更新（也就是先更新子節點，再更新父節點）。
        updateHeight(x);
        updateHeight(y);

        // 回傳新的根節點
        return y;
    }
    
    // 自動平衡調整函式
    AVLNode<T>* rebalance(AVLNode<T>* node) {
        if (node == nullptr)    return nullptr;

        // 更新當前節點高度
        updateHeight(node);

        // 取得平衡因子
        int balance = getBalanceFactor(node);
        
        // 檢查是否需要旋轉
        // LL Case: 左重，且左子節點也是左重 (或平衡)
        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rightRotate(node);                   // 單純右旋
        }

        // LR Case: 左重，但左子節點是右重
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);        // 左子樹先左旋
            return rightRotate(node);                   // 再對自己右旋
        }

        // RR Case: 右重，且右子節點也是右重 (或平衡)   
        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }

        // RL Case: 右重，但右子節點是左重 
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);     // 右子樹先右旋
            return leftRotate(node);                    // 再對自己左旋
        }
        
        return node;
    }
    // 插入節點 (Insert)
    AVLNode<T>* insert_helper(AVLNode<T>* node, T val, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return new AVLNode<T>(val);
        }

        if (val < node->data) {
            node->left = insert_helper(node->left, val, inserted);
        } else if (val > node->data) {
            node->right = insert_helper(node->right, val, inserted);
        } else {
            inserted = false;   // 數值已存在，不插入
            return node;
        }
        // 回溯時自動平衡與更新高度
        return rebalance(node);
    }
    
    // 刪除節點 (Remove)
    // 輔助函式，遞迴刪除指定值節點
    AVLNode<T>* remove_helper(AVLNode<T>* node, T val, bool& removed) {
        if (node == nullptr) {
            removed = false;
            return nullptr;
        }
        // 1. 尋找要刪除的節點
        if (val < node->data) {
            node->left = remove_helper(node->left, val, removed);
        } else if (val > node->data) {
            node->right = remove_helper(node->right, val, removed);
        } else {
            // 找到目標節點了！
            removed = true;
            // 情況 1 & 2: 無子節點，或只有單一子節點
            if (node->left == nullptr) {
                AVLNode<T>* temp = node->right;
                delete node;
                return temp; // 直接回傳子節點，由上層節點回溯時進行平衡
            } else if (node->right == nullptr) {
                AVLNode<T>* temp = node->left;
                delete node;
                return temp;
            }

            // 情況 3: 有兩個子節點
            // 找出右子樹中的最小值節點 (Inorder Successor) 來替代
            AVLNode<T>* temp = find_min(node->right);
            node->data = temp->data;
            // 在右子樹中遞迴刪除該替代節點
            bool dummy = false;
            node->right = remove_helper(node->right, temp->data, dummy);
        }        
        // 如果刪除後整棵樹空了，直接回傳
        if (node == nullptr) return nullptr;

        // 回溯時自動平衡與更新高度
        return rebalance(node);
    }
    // 尋找給定子樹的最小值節點
    AVLNode<T>* find_min(AVLNode<T>* node) const {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // 尋找給定子樹的最大值節點
    AVLNode<T>* find_max(AVLNode<T>* node) const {
        if (node == nullptr) return nullptr;
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    // 中序走訪輔助函式
    void inorder_helper(AVLNode<T>* node, std::vector<T>& result) const {
        if (node == nullptr) return;
        inorder_helper(node->left, result);
        result.push_back(node->data);
        inorder_helper(node->right, result);
    }    

public:
    AVLTree() : root(nullptr), size_(0) {}

    // 複製構造函式
    AVLTree(const AVLTree& other) : root(nullptr), size_(0) {
        root = copy_helper(other.root);
        size_ = other.size_;
    }

    // 複製賦值運算符
    AVLTree& operator=(const AVLTree& other) {
        if (this != &other) {
            AVLTree temp(other);
            std::swap(root, temp.root);
            std::swap(size_, temp.size_);
        }
        return *this;
    }

    // 析構函式
    ~AVLTree() {
        clear_helper(root);
    }

    bool insert(T val) {
        bool inserted = false;
        root = insert_helper(root, val, inserted);
        if (inserted) {
            size_++;
        }
        return inserted;
    }
    
    bool remove(T val) {
        bool removed = false;
        root = remove_helper(root, val, removed);
        if (removed) {
            size_--;
        }
        return removed;
    }

    // 取得節點個數
    size_t size() const {
        return size_;
    }

    // 檢查是否為空
    bool isEmpty() const {
        return size_ == 0;
    }   

    // 取得樹的高度
    int height() const {
        return getHeight(root);
    }

    // 中序走訪
    std::vector<T> inorder() const {
        std::vector<T> result;
        inorder_helper(root, result);
        return result;
    }
    
    // 層序走訪 (Level-Order) — 驗證樹的立體結構是否平衡的關鍵
    std::vector<std::vector<T>> levelOrder() const {
        std::vector<std::vector<T>> result;
        if (root == nullptr) return result;
        Queue<AVLNode<T>*> q;
        q.enqueue(root);
        while (!q.isEmpty()) {
            size_t levelSize = q.size();
            std::vector<T> currentLevel;
            for (size_t i = 0; i < levelSize; ++i) {
                AVLNode<T>* node = q.dequeue();
                currentLevel.push_back(node->data);
                if (node->left != nullptr)  q.enqueue(node->left);
                if (node->right != nullptr) q.enqueue(node->right);
            }
            result.push_back(currentLevel);
        }
        return result;
    }

    
};