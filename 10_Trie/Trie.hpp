#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>

// ---------------------------------------------------------
// 1. 字典樹節點 (TrieNode) 結構
// ---------------------------------------------------------
struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord = false;

    TrieNode() = default;
    ~TrieNode() = default;
};

// ---------------------------------------------------------
// 2. 字典樹 (Trie) 類別
// ---------------------------------------------------------
class Trie {
private:
    TrieNode* root;

    // 內部遞迴輔助函式：清理整棵樹
    void clear_helper(TrieNode* node) {
        if (node == nullptr) return;
        for (auto& pair : node->children)
            clear_helper(pair.second);
        delete node;
    }

    // 內部遞迴輔助函式：複製整棵樹 (用於深層複製)
    TrieNode* copy_helper(const TrieNode* other) {
        if (other == nullptr) return nullptr;
        TrieNode* newNode = new TrieNode();
        newNode->isEndOfWord = other->isEndOfWord;
        for (auto& pair : other->children) {
            newNode->children[pair.first] = copy_helper(pair.second);
        }
        return newNode;
    }

    // 內部遞迴輔助函式：收集所有具有給定前綴的單字 (用於自動補全)
    void collect_words(TrieNode* node, std::string current_prefix,
        std::vector<std::string>& result) const {
        if (node == nullptr) return;
        if (node->isEndOfWord) {
            result.push_back(current_prefix);
        }
        for (auto& pair : node->children) {
            collect_words(pair.second, current_prefix + pair.first, result);
        }
    }

public:
    // 構造函式：初始化空字典樹
    Trie() : root(new TrieNode()) {}

    // 析構函式：清理記憶體
    ~Trie() {
        clear_helper(root);
    }

    // 複製構造函式 (深層複製)
    Trie(const Trie& other) : root(copy_helper(other.root)) {}

    // 拷貝賦值運算子
    Trie& operator=(const Trie& other) {
        if (this != &other) {
            Trie temp(other);
            std::swap(root, temp.root);
        }
        return *this;
    }

    // 核心 API
    void insert(const std::string& word);
    bool search(const std::string& word) const;
    bool startsWith(const std::string& prefix) const;

    // 進階 API：自動補全 (Autocomplete)
    std::vector<std::string> autocomplete(const std::string& prefix) const;
};

void Trie::insert(const std::string& word) {
    TrieNode* curr = root;
    for (char c : word) {
        if (curr->children.find(c) == curr->children.end()) {
            curr->children[c] = new TrieNode();
        }
        curr = curr->children[c];
    }
    curr->isEndOfWord = true;
}

bool Trie::search(const std::string& word) const {
    TrieNode* curr = root;
    for (char c : word) {
        if (curr->children.find(c) == curr->children.end()) {
            return false;
        }
        curr = curr->children[c];
    }
    return curr->isEndOfWord;
}

bool Trie::startsWith(const std::string& prefix) const {
    TrieNode* curr = root;
    for (char c : prefix) {
        if (curr->children.find(c) == curr->children.end()) {
            return false;
        }
        curr = curr->children[c];
    }
    return true;
}

std::vector<std::string> Trie::autocomplete(const std::string& prefix) const {
    TrieNode* curr = root;
    for (char c : prefix) {
        if (curr->children.find(c) == curr->children.end()) {
            return {}; // 找不到任何字詞
        }
        curr = curr->children[c];
    }
    
    std::vector<std::string> result;
    collect_words(curr, prefix, result);
    return result;
}
    