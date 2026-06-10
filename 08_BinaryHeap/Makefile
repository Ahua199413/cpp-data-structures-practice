# 08_BinaryHeap/Makefile

# 包含共用的編譯選項和變數
include ../common.mk

# 專案特定設定
TARGET = binary_heap_test
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

# 依賴的標頭檔
HEADERS = BinaryHeap.hpp PriorityQueue.hpp

# 預設目標
all: $(TARGET)

# 連結目標檔案產生執行檔
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# 編譯 .cpp 檔案產生 .o 檔案
main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# 清除編譯產物
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
