# common.mk

# 編譯器
CXX = g++

# 通用編譯旗標：啟用警告、指定 C++ 
# -Wall: 		啟用所有警告
# -Wextra:		啟用額外警告
# -std=c++17: 	指定使用 C++17 標準
# -g: 			嵌入除錯資訊 (Debugging info)
# -pedantic: 	嚴格遵守標準，對非標準行為給警告或錯誤
CXXFLAGS = -Wall -Wextra -std=c++17 -pedantic

# 連結旗標 (如果需要額外函式庫，例如 -lm, -lpthread 等)
LDFLAGS =