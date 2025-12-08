#include "DynamicArray.hpp"
#include <stdexcept>

DynamicArray::DynamicArray() : capacity(4), length(0)
{
    data = new int[capacity];
}

DynamicArray::~DynamicArray()
{
    delete[] data;
}

void DynamicArray::resize(int newCap)
{
    int *newData = new int[newCap];
    for (int i = 0; i < length; i++)
        newData[i] = data[i];
    delete[] data;
    data = newData;
    capacity = newCap;
}

void DynamicArray::push_back(int value)
{
    if (length == capacity)
        resize(capacity * 2);
    data[length++] = value;
}

void DynamicArray::pop_back()
{
    if (length == 0)
        return;
    length--;
}

int DynamicArray::get(int index) const
{
    if (index < 0 || index >= length)
        throw std::out_of_range("Index error");
}
void DynamicArray::set(int index, int value)
{
    if (index < 0 || index >= length)
        throw std::out_of_range("Index error");
    data[index] = value;
}
int DynamicArray::size() const
{
    return length;
}