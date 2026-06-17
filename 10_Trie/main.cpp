#include "Trie.hpp"
#include "../TestFramework.h"
#include <string>
#include <vector>
#include <algorithm>

// 輔助函式：檢查字串向量中是否包含特定元素
bool contains_word(const std::vector<std::string>& vec, const std::string& target) {
    return std::find(vec.begin(), vec.end(), target) != vec.end();
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

TEST_SUITE(Trie_Autocomplete_Test)
    Trie trie;
    trie.insert("app");
    trie.insert("apple");
    trie.insert("application");
    trie.insert("banana");
    trie.insert("bat");

    std::vector<std::string> results = trie.autocomplete("app");

    TEST_EQUAL(3, results.size(), "Autocomplete 'app' should find 3 words");
    TEST_EQUAL(true, contains_word(results, "app"), "Contains 'app'");
    TEST_EQUAL(true, contains_word(results, "apple"), "Contains 'apple'");
    TEST_EQUAL(true, contains_word(results, "application"), "Contains 'application'");
    TEST_EQUAL(false, contains_word(results, "banana"), "Should not contain 'banana'");

    results = trie.autocomplete("b");
    TEST_EQUAL(2, results.size(), "Autocomplete 'b' should find 2 words");
    TEST_EQUAL(true, contains_word(results, "banana"), "Contains 'banana'");
    TEST_EQUAL(true, contains_word(results, "bat"), "Contains 'bat'");

    results = trie.autocomplete("c");
    TEST_EQUAL(0, results.size(), "Autocomplete 'c' should find 0 words");
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

void run_all_tests() {
    Trie_Core_Operations();
    Trie_Autocomplete_Test();
    Trie_Resource_Management();
}

int main() {
    run_all_tests();
    print_test_report();
    return (g_tests_failed == 0) ? 0 : 1;
}
