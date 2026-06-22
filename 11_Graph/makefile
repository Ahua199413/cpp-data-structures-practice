# 11_Graph/Makefile

include ../common.mk

TARGET = graph_test
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = Graph.hpp ../TestFramework.h ../04_Queue/Queue.hpp ../02_LinkedList/LinkedList.hpp

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
