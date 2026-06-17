#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
#include <stdexcept>

// ---------------------------------------------------------
// 1. 字典樹節點 (TrieNode) 結構
// ---------------------------------------------------------
struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord = false;
    int frequency = 0;

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
        std::vector<std::pair<std::string, int>>& result) const {
        if (node == nullptr) return;
        if (node->isEndOfWord) {
            result.push_back({current_prefix, node->frequency});
        }
        for (auto& pair : node->children) {
            collect_words(pair.second, current_prefix + pair.first, result);
        }
    }
    bool remove_helper(TrieNode* curr, const std::string& word, size_t index) {
        if (curr == nullptr) return false;
        // 1. Base Case: 走到了單字的最後一個字元所在的節點
        
        if (index == word.length()) {
            // 如果它不是單字的結尾，說明這單字根本不在字典樹中
            if (!curr->isEndOfWord) return false;

            // 將結尾標記取消
            curr->isEndOfWord = false;
            curr->frequency = 0; // 重置詞頻

            // 如果它沒有任何子節點，代表它是葉子節點，可以被父節點刪除
            return curr->children.empty();
        }
        char ch = word[index];
        // 如果路徑中斷，說明單字不存在
        if (curr->children.find(ch) == curr->children.end()) {
            return false;
        }

        // 2. 遞迴向下，並接收子節點的回傳值
        TrieNode* child_node = curr->children[ch];
        bool should_delete_child = remove_helper(child_node, word, index + 1);

        // 3. 回溯階段 (Backtracking)：如果子節點說它可以被刪除
        if (should_delete_child) {
            delete child_node;             // 1. 釋放子節點記憶體
            curr->children.erase(ch);      // 2. 從 Map 中把字元連結斷開

            // 4. 重點：子節點刪除後，檢查「我自己」是不是也變空了？
            // 如果我自己也不是別人的結尾，且現在也沒有子節點了，那我也能被我的父節點刪除
            return !curr->isEndOfWord && curr->children.empty();
        }
        return false;
        
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
    bool remove(const std::string& word);

    // 進階 API：自動補全 (Autocomplete)
    std::vector<std::pair<std::string, int>> autocomplete(const std::string& prefix) const;
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
    curr->frequency++;
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

std::vector<std::pair<std::string, int>> Trie::autocomplete(const std::string& prefix) const {
    TrieNode* curr = root;
    for (char c : prefix) {
        if (curr->children.find(c) == curr->children.end()) {
            return {}; // 找不到任何字詞
        }
        curr = curr->children[c];
    }
    
    std::vector<std::pair<std::string, int>> result;
    collect_words(curr, prefix, result);
    sort(result.begin(), result.end(), [](const auto& a, const auto& b){
        if (a.second != b.second) {
            return a.second > b.second;
        }
        return a.first < b.first;
    });
    return result;
}
    

bool Trie::remove(const std::string& word) {
    if (word.empty()) return false;
    return remove_helper(root, word, 0);
}