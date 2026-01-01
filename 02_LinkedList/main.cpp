#include "LinkedList.h"       // 包含您的鏈結串列實現
#include "../TestFramework.h" // 包含單元測試框架
#include <iostream>
#include <stdexcept>
#include <string>

// 輔助函式：將鏈結串列內容轉換成字串 (方便 TEST_EQUAL 比較)
template <typename T>
std::string list_to_string(const LinkedList<T> &list)
{
    std::string s = "[";
    for (size_t i = 0; i < list.getSize(); i++)
    {
    }
}