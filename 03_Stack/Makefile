# 03_Stack/Makefile

# 包含共用的編譯選項和變數
include ../common.mk

# 定義目標名稱 (例如，可執行檔名稱)
TARGET = test_stack

# 定義需要編譯的原始碼檔案
# main.cpp 包含測試邏輯，同時依賴 Stack.h 和 TestFramework.h
SRCS = main.cpp
# 將原始碼編譯成物件檔案 (.o)
OBJS = $(SRCS:.cpp=.o)
# 關鍵變更：明確列出 main.cpp 所依賴的所有標頭檔
# 注意：TestFramework.h 在上層目錄，需要使用相對路徑
HEADERS = Stack.hpp ../TestFramework.h

# 預設目標：編譯所有物件檔並連結成 TARGET
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# 編譯 .cpp 檔案到 .o 檔案
# < : 依賴 (dependency)
# $@ : 目標 (target)
# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@
# 編譯規則：現在 main.o 依賴於 main.cpp 和 HEADERS
main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理規則
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)