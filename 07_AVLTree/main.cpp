#include "AVLTree.hpp"
#include "../TestFramework.h"
#include <vector>
#include <string>

// 輔助函式：將 vector 轉為字串便於比對
template <typename T>
std::string vector_to_string(const std::vector<T> &vec) {
    std::string s = "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        s += std::to_string(vec[i]);
        if (i != vec.size() - 1) s += ", ";
    }
    s += "]";
    return s;
}

// 輔助函式：將 2D vector (Level Order) 轉為字串
template <typename T>
std::string level_order_to_string(const std::vector<std::vector<T>> &levels) {
    std::string s = "[";
    for (size_t i = 0; i < levels.size(); ++i) {
        s += vector_to_string(levels[i]);
        if (i != levels.size() - 1) s += ", ";
    }
    s += "]";
    return s;
}

// ==========================================================
// 測試套件 1: 自動平衡 (旋轉測試)
// ==========================================================
TEST_SUITE(AVL_Auto_Balance_Test)
AVLTree<int> avl;

// 依序插入 10, 20, 30 (會觸發 RR 旋轉)
avl.insert(10);
avl.insert(20);
avl.insert(30);

// 若成功旋轉，根節點應變為 20，左右為 10 與 30
TEST_EQUAL(2, avl.height(), "RR Rotate: Height should be 2");
TEST_EQUAL(std::string("[[20], [10, 30]]"), level_order_to_string(avl.levelOrder()), "RR Rotate Structure");

// 繼續插入 40, 50 (會再次觸發旋轉)
avl.insert(40);
avl.insert(50);
TEST_EQUAL(3, avl.height(), "Height after inserting 50");
TEST_EQUAL(std::string("[[20], [10, 40], [30, 50]]"), level_order_to_string(avl.levelOrder()), "Structure after inserting 50");
END_SUITE

// ==========================================================
// 測試套件 2: 刪除與重新平衡
// ==========================================================
TEST_SUITE(AVL_Deletion_And_Rebalance_Test)
AVLTree<int> avl;
avl.insert(50);
avl.insert(30);
avl.insert(70);
avl.insert(20);
avl.insert(40);
avl.insert(60);
avl.insert(80); // 建立一個滿二元樹，高度為 3

TEST_EQUAL(3, avl.height(), "Initial balanced height");

// 刪除葉子節點 20 
TEST_EQUAL(true, avl.remove(20), "Remove 20");
TEST_EQUAL(6, avl.size(), "Size after deletion");

// 刪除 30，應該會用 40 來替代
TEST_EQUAL(true, avl.remove(30), "Remove two-child node 30");
TEST_EQUAL(std::string("[40, 50, 60, 70, 80]"), vector_to_string(avl.inorder()), "Inorder check after deleting 30");
END_SUITE

void run_all_tests() {
    AVL_Auto_Balance_Test();
    AVL_Deletion_And_Rebalance_Test();
}

int main() {
    run_all_tests();
    print_test_report();
    return (g_tests_failed == 0) ? 0 : 1;
}
