#include "HashTable.hpp"
#include "../TestFramework.h"
#include <string>

// 用於碰撞測試的「爛雜湊函數」，讓所有 string 的 Hash 值都為 0
struct BadHash {
    size_t operator()(const std::string&) const { 
        return 0;
    }
};

TEST_SUITE(HashTable_Core_Operations)
    HashTable<std::string, int> ht;
    TEST_EQUAL(true, ht.isEmpty(), "New HashTable is empty");
    TEST_EQUAL(0, ht.size(), "New HashTable size is 0");
    // 插入元素
    TEST_EQUAL(true, ht.insert("apple", 100), "Insert apple");
    TEST_EQUAL(true, ht.insert("banana", 200), "Insert banana");
    TEST_EQUAL(2, ht.size(), "Size check");
    // 搜尋元素
    int val = 0;
    TEST_EQUAL(true, ht.search("apple", val), "Search apple");
    TEST_EQUAL(100, val, "Search apple value");
    TEST_EQUAL(true, ht.search("banana", val), "Search banana");
    TEST_EQUAL(200, val, "Search banana value");
    // 更新重複元素
    TEST_EQUAL(false, ht.insert("apple", 999), "Update apple (should return false)");
    TEST_EQUAL(2, ht.size(), "Size remains same after update");
    TEST_EQUAL(true, ht.search("apple", val), "Search apple again");
    TEST_EQUAL(999, val, "Updated apple value");
    // 刪除元素
    TEST_EQUAL(true, ht.remove("apple"), "Remove apple");
    TEST_EQUAL(1, ht.size(), "Size decremented");
    TEST_EQUAL(false, ht.search("apple", val), "Search deleted apple should fail");
    TEST_EQUAL(true, ht.search("banana", val), "Search banana is still fine");
END_SUITE

TEST_SUITE(HashTable_Collision_And_Tombstone)
    // 透過 BadHash 強制所有 Key (A, B, C) 落在相同 index (0)
    HashTable<std::string, int, BadHash> ht;
    ht.insert("A", 10); // 放在 0
    ht.insert("B", 20); // 放在 1 (線性探測碰撞)
    ht.insert("C", 30); // 放在 2 (線性探測碰撞)
    TEST_EQUAL(3, ht.size(), "Size of collided table");
    // 刪除中間的 "B"，這會在 index 1 留下 Tombstone (DELETED 狀態)
    TEST_EQUAL(true, ht.remove("B"), "Remove B");
    // 測試：搜尋後方的 "C"，必須能夠「穿透」中間的 DELETED 狀態成功找到
    int val = 0;
    TEST_EQUAL(true, ht.search("C", val), "Search C should succeed through deleted B");
    TEST_EQUAL(30, val, "C value check");
    // 測試：此時插入新的 Key "D"，必須能夠「重用」剛剛被刪除的 index 1 位置
    TEST_EQUAL(true, ht.insert("D", 40), "Insert D");
    TEST_EQUAL(true, ht.search("D", val), "Search D");
    TEST_EQUAL(40, val, "D value check");
END_SUITE

void run_all_tests() {
    HashTable_Core_Operations();
    HashTable_Collision_And_Tombstone();
}
int main() {
    run_all_tests();
    print_test_report();
    return (g_tests_failed == 0) ? 0 : 1;
}