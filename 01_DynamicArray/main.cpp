#include "DynamicArray.hpp"
#include <iostream>

int main()
{
    DynamicArray arr;

    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr.get(i) << " ";
    }

    return 0;
}
