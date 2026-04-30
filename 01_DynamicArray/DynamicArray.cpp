#include "DynamicArray.hpp"
#include <stdexcept>

DynamicArray::DynamicArray() : data(new int[2]), capacity(2), length(0) {}

DynamicArray::~DynamicArray()
{
    delete[] data;
}

void DynamicArray::resize(int newCap)
{
    int *newData = new int[newCap];
    for (int i = 0; i < length; ++i)
    {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCap;
}

void DynamicArray::push_back(int value)
{
    if (length == capacity)
    {
        resize(capacity * 2);
    }
    data[length++] = value;
}

void DynamicArray::pop_back()
{
    if (length == 0)
    {
        throw std::out_of_range("Array is empty.");
    }
    --length;
}

int DynamicArray::get(int index) const
{
    if (index < 0 || index >= length)
    {
        throw std::out_of_range("Index out of range.");
    }
    return data[index];
}

void DynamicArray::set(int index, int value)
{
    if (index < 0 || index >= length)
    {
        throw std::out_of_range("Index out of range.");
    }
    data[index] = value;
}

int DynamicArray::size() const
{
    return length;
}
