# 10_Trie/Makefile

include ../common.mk

TARGET = trie_test
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = Trie.hpp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
