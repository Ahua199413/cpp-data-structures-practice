# 01_DynamicArray/Makefile

# 包含共用的編譯選項和變數
include ../common.mk

# 專案特定設定
TARGET = dynamic_array_test
SRCS = main.cpp DynamicArray.cpp
OBJS = $(SRCS:.cpp=.o)

# 預設目標：編譯所有物件檔並連結成 TARGET
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# 通用編譯規則：告訴 make 如何從 .cpp 檔案創建 .o 檔案
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 依賴關係：必須手動聲明頭文件依賴，確保頭文件變動時重新編譯
main.0: DynamicArray.hpp
DynamicArray.0: DynamicArray.hpp

# 清理規則
clean:
	rm -f $(TARGET) $(OBJS)