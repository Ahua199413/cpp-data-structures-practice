# 01_DynamicArray/Makefile

# 包含共用的編譯選項和變數
include ../common.mk

# 專案特定設定
TARGET = linked_list_test
SRCS = main.cpp
OBJS = main.o

# 依賴的標頭檔 (當這些檔案變動時，需要重新編譯)
# LinkedList.hpp 在當前目錄，TestFramework.h 在上層目錄
HEADERS = LinkedList.hpp ../TestFramework.h

# 預設目標
all: $(TARGET)

# 連結目標檔案產生執行檔
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# 編譯 .cpp 檔案產生 .o 檔案
# 我們明確加入 $(HEADERS) 作為依賴項
main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# 清除編譯產物
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)