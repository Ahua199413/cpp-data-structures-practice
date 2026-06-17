#include "Trie.hpp"
#include "../TestFramework.h"
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

// 輔助函式：檢查字串向量中是否包含特定元素
bool contains_word(const std::vector<std::pair<std::string, int>>& vec, const std::string& target) {
    for (const auto& pair : vec) {
        if (pair.first == target) return true;
    }
    return false;
}

TEST_SUITE(Trie_Core_Operations)
    Trie trie;

    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");

    // 精確搜尋測試
    TEST_EQUAL(true, trie.search("apple"), "Search 'apple'");
    TEST_EQUAL(true, trie.search("app"), "Search 'app'");
    TEST_EQUAL(false, trie.search("appl"), "Search 'appl' (incomplete word)");
    TEST_EQUAL(false, trie.search("bananaa"), "Search 'bananaa'");

    // 前綴搜尋測試
    TEST_EQUAL(true, trie.startsWith("app"), "Starts with 'app'");
    TEST_EQUAL(true, trie.startsWith("appl"), "Starts with 'appl'");
    TEST_EQUAL(true, trie.startsWith("ban"), "Starts with 'ban'");
    TEST_EQUAL(false, trie.startsWith("bat"), "Starts with 'bat'");
END_SUITE

TEST_SUITE(Trie_Resource_Management)
    Trie original;
    original.insert("car");
    original.insert("cat");

    // 複製建構子測試 (Deep Copy)
    Trie copy(original);
    TEST_EQUAL(true, copy.search("car"), "Copy contains 'car'");

    // 修改原 Trie，不應該影響副本
    original.insert("cab");
    TEST_EQUAL(false, copy.search("cab"), "Copy isolates from original modifications");
END_SUITE

TEST_SUITE(Trie_Autocomplete_Test)
    Trie trie;
    // 手動模擬詞頻：app 插入 3 次, application 2 次, apple 1 次
    trie.insert("app");
    trie.insert("app");
    trie.insert("app");

    trie.insert("application");
    trie.insert("application");

    trie.insert("apple");

    trie.insert("banana");

    std::vector<std::pair<std::string, int>> results = trie.autocomplete("app");

    TEST_EQUAL(3, results.size(), "Autocomplete 'app' should find 3 words");
    
    // 驗證順序是否依照詞頻降序：app (3) -> application (2) -> apple (1)
    TEST_EQUAL("app", results[0].first, "Top Result: app");
    TEST_EQUAL("application", results[1].first, "Second Result: application");
    TEST_EQUAL("apple", results[2].first, "Third Result: apple");
END_SUITE


void run_all_tests() {
    Trie_Core_Operations();
    Trie_Autocomplete_Test();
    Trie_Resource_Management();
    Trie_Autocomplete_Test();
}

int main() {
    run_all_tests();
    print_test_report();
    return (g_tests_failed == 0) ? 0 : 1;
}
