# 06_BinarySearchTree/Makefile

# 包含共用的編譯選項和變數
include ../common.mk

# 定義目標名稱 (可執行檔名稱)
TARGET = bst_test

# 定義需要編譯的原始碼檔案
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = BST.hpp ../TestFramework.h ../04_Queue/Queue.hpp ../02_LinkedList/LinkedList.hpp

# 預設目標：編譯所有物件檔並連結成 TARGET
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# 編譯規則
main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理規則
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
