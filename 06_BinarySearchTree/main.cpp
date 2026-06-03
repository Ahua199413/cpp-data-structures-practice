#include "BST.hpp"
#include "../TestFramework.h"
#include <vector>
#include <string>

// 輔助函式：將 vector 轉為字串便於比對
template <typename T>
std::string vector_to_string(const std::vector<T> &vec)
{
    std::string s = "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        s += std::to_string(vec[i]);
        if (i != vec.size() - 1)
        {
            s += ", ";
        }
    }
    s += "]";
    return s;
}

// 輔助函式：將 2D vector (Level Order) 轉為字串便於比對
template <typename T>
std::string level_order_to_string(const std::vector<std::vector<T>> &levels)
{
    std::string s = "[";
    for (size_t i = 0; i < levels.size(); ++i)
    {
        s += vector_to_string(levels[i]);
        if (i != levels.size() - 1)
        {
            s += ", ";
        }
    }
    s += "]";
    return s;
}

// ==========================================================
// 測試套件 1: 插入與基本屬性
// ==========================================================
TEST_SUITE(BST_Insertion_And_Search_Test)
BST<int> bst;

TEST_EQUAL(true, bst.isEmpty(), "New BST is empty");
TEST_EQUAL(0, bst.size(), "New BST size is 0");

// 測試插入首個節點 (根節點)
TEST_EQUAL(true, bst.insert(50), "Insert 50 (Root)");
TEST_EQUAL(1, bst.size(), "Size after 1 insertion");
TEST_EQUAL(false, bst.isEmpty(), "BST should not be empty");

// 測試插入其他節點
TEST_EQUAL(true, bst.insert(30), "Insert 30 (Left child)");
TEST_EQUAL(true, bst.insert(70), "Insert 70 (Right child)");
TEST_EQUAL(true, bst.insert(20), "Insert 20 (Left-Left)");
TEST_EQUAL(true, bst.insert(40), "Insert 40 (Left-Right)");
TEST_EQUAL(5, bst.size(), "Size after 5 insertions");

// 測試重複插入 (應該失敗)
TEST_EQUAL(false, bst.insert(30), "Insert duplicate value 30 should fail");
TEST_EQUAL(5, bst.size(), "Size remains 5 after duplicate attempt");

// 測試搜尋 (Search)
TEST_EQUAL(true, bst.search(50), "Search existing root 50");
TEST_EQUAL(true, bst.search(20), "Search existing leaf 20");
TEST_EQUAL(true, bst.search(40), "Search existing middle 40");
TEST_EQUAL(false, bst.search(100), "Search non-existing 100");
TEST_EQUAL(false, bst.search(10), "Search non-existing 10");
END_SUITE

// ==========================================================
// 測試套件 2: 樹的走訪 (Traversals)
// ==========================================================
TEST_SUITE(BST_Traversal_Test)
BST<int> bst;
bst.insert(50);
bst.insert(30);
bst.insert(70);
bst.insert(20);
bst.insert(40);
bst.insert(60);
bst.insert(80);

// 中序走訪 (應該得到遞增排序)
std::vector<int> in = bst.inorder();
TEST_EQUAL(std::string("[20, 30, 40, 50, 60, 70, 80]"), vector_to_string(in), "Inorder traversal check");

// 前序走訪 (根 -> 左 -> 右)
std::vector<int> pre = bst.preorder();
TEST_EQUAL(std::string("[50, 30, 20, 40, 70, 60, 80]"), vector_to_string(pre), "Preorder traversal check");

// 後序走訪 (左 -> 右 -> 根)
std::vector<int> post = bst.postorder();
TEST_EQUAL(std::string("[20, 40, 30, 60, 80, 70, 50]"), vector_to_string(post), "Postorder traversal check");
END_SUITE

// ==========================================================
// 測試套件 3: 刪除操作 (Deletion Cases)
// ==========================================================
TEST_SUITE(BST_Deletion_Test)
BST<int> bst;
bst.insert(50);
bst.insert(30);
bst.insert(70);
bst.insert(20);
bst.insert(40);
bst.insert(60);
bst.insert(80);

// 測試刪除不存在的值
TEST_EQUAL(false, bst.remove(99), "Remove non-existing value 99 should fail");
TEST_EQUAL(7, bst.size(), "Size should remain 7");

// 情況 1: 刪除葉子節點 (Leaf Node)
TEST_EQUAL(true, bst.remove(20), "Remove leaf node 20");
TEST_EQUAL(6, bst.size(), "Size after removing 20");
TEST_EQUAL(false, bst.search(20), "Leaf 20 is no longer searchable");
TEST_EQUAL(std::string("[30, 40, 50, 60, 70, 80]"), vector_to_string(bst.inorder()), "Inorder after removing 20");

// 情況 2: 刪除只有一個子節點的節點
// 移除 20 後，30 只有右子節點 40
TEST_EQUAL(true, bst.remove(30), "Remove single-child node 30");
TEST_EQUAL(5, bst.size(), "Size after removing 30");
TEST_EQUAL(false, bst.search(30), "Node 30 is no longer searchable");
TEST_EQUAL(true, bst.search(40), "Child node 40 is still preserved");
TEST_EQUAL(std::string("[40, 50, 60, 70, 80]"), vector_to_string(bst.inorder()), "Inorder after removing 30");

// 情況 3: 刪除具有兩個子節點的節點 (例如根節點 50)
// 目前樹結構中，50 的左子樹有 40，右子樹有 70(根), 60(左), 80(右)
// 刪除 50 時，右子樹最小值為 60 (Inorder Successor) 會替代 50 的位置，然後在右子樹刪除 60
TEST_EQUAL(true, bst.remove(50), "Remove two-children node 50 (Root)");
TEST_EQUAL(4, bst.size(), "Size after removing root 50");
TEST_EQUAL(false, bst.search(50), "Old root 50 is no longer searchable");
TEST_EQUAL(std::string("[40, 60, 70, 80]"), vector_to_string(bst.inorder()), "Inorder after removing root 50");
END_SUITE

// ==========================================================
// 測試套件 4: 資源管理 (深層複製與記憶體安全)
// ==========================================================
TEST_SUITE(BST_Resource_Management_Test)
BST<int> original;
original.insert(50);
original.insert(25);
original.insert(75);

// 1. 複製建構子 (Copy Constructor)
BST<int> copy = original;
TEST_EQUAL(3, copy.size(), "Copy constructor: size check");
TEST_EQUAL(true, copy.search(25), "Copy constructor: child search");

// 刪除 original 的節點，copy 不應該受影響 (深層複製隔離檢查)
original.remove(25);
TEST_EQUAL(2, original.size(), "Original size after removal");
TEST_EQUAL(3, copy.size(), "Copy size remains 3");
TEST_EQUAL(true, copy.search(25), "Copy still contains 25");

// 2. 複製賦值運算子 (Copy Assignment)
BST<int> assigned;
assigned.insert(99);
assigned = copy; // 應該釋放 99 並深層複製 copy 的內容 (50, 25, 75)

TEST_EQUAL(3, assigned.size(), "Copy assignment: size check");
TEST_EQUAL(false, assigned.search(99), "Old value 99 should be cleared");
TEST_EQUAL(true, assigned.search(25), "Copy assignment: child search");

// 刪除 copy 的節點，assigned 不應該受影響
copy.remove(75);
TEST_EQUAL(2, copy.size(), "Copy size after removal");
TEST_EQUAL(3, assigned.size(), "Assigned size remains 3");
TEST_EQUAL(true, assigned.search(75), "Assigned still contains 75");
END_SUITE

// ==========================================================
// 測試套件 5: 進階演算法 (高度、平衡判定與層序走訪)
// ==========================================================
TEST_SUITE(BST_Advanced_Algorithms_Test)
// 1. 空樹測試
BST<int> empty_tree;
TEST_EQUAL(0, empty_tree.height(), "Empty tree height is 0");
TEST_EQUAL(true, empty_tree.isBalanced(), "Empty tree is balanced");
TEST_EQUAL(std::string("[]"), level_order_to_string(empty_tree.levelOrder()), "Empty tree level order");

// 2. 平衡樹測試
BST<int> bst;
bst.insert(50);
bst.insert(30);
bst.insert(70);
bst.insert(20);
bst.insert(40);
bst.insert(60);
bst.insert(80);

TEST_EQUAL(3, bst.height(), "Balanced tree height is 3");
TEST_EQUAL(true, bst.isBalanced(), "Balanced tree check");
TEST_EQUAL(std::string("[[50], [30, 70], [20, 40, 60, 80]]"), level_order_to_string(bst.levelOrder()), "Balanced tree level order");

// 3. 非平衡樹測試
BST<int> skewed;
skewed.insert(10);
skewed.insert(20);
skewed.insert(30);
skewed.insert(40);

TEST_EQUAL(4, skewed.height(), "Skewed tree height is 4");
TEST_EQUAL(false, skewed.isBalanced(), "Skewed tree is unbalanced");
TEST_EQUAL(std::string("[[10], [20], [30], [40]]"), level_order_to_string(skewed.levelOrder()), "Skewed tree level order");
END_SUITE

void run_all_tests()
{
    BST_Insertion_And_Search_Test();
    BST_Traversal_Test();
    BST_Deletion_Test();
    BST_Resource_Management_Test();
    BST_Advanced_Algorithms_Test();
}

int main()
{
    run_all_tests();
    print_test_report();
    return (g_tests_failed == 0) ? 0 : 1;
}
