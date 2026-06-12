# 09_HashTable/Makefile

include ../common.mk

TARGET = hashtable_test
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = HashTable.hpp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET) 