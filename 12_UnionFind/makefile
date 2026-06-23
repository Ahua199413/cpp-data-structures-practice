# 12_UnionFind/Makefile

include ../common.mk

TARGET = union_find_test
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = UnionFind.hpp ../TestFramework.h

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
