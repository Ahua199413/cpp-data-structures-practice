#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

class DynamicArray
{
private:
    int *data;
    int capacity;
    int length;

    void resize(int newCap);

public:
    DynamicArray();
    ~DynamicArray();

    // Copy constructor
    DynamicArray(const DynamicArray &other);
    // Copy assignment operator
    DynamicArray &operator=(const DynamicArray &other);

    void push_back(int value);
    void pop_back();
    int get(int index) const;
    void set(int index, int value);
    int size() const;
};

#endif