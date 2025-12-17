#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <algorithm>

template <typename T>
class Vector {
private:
    T* data;          // con trỏ đến mảng động
    size_t _size;      // số phần tử hiện có
    size_t cap;  // sức chứa hiện tại

    void resize(size_t newCapacity) {
        if (newCapacity < _size) newCapacity = _size;  // không được nhỏ hơn size

        T* newData = new T[newCapacity];
        
        // Copy các phần tử cũ sang
        for (size_t i = 0; i < _size; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        cap = newCapacity;
    }
    public:
 
Vector(size_t fistCap = 4) : _size(0),cap(fistCap){
    data = new T[cap];
}
Vector(const Vector& other) : _size(other._size), cap(other.cap) {
        data = new T[cap];
        for (size_t i = 0; i < _size; ++i) {
            data[i] = other.data[i];
        }
    }
Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;

            _size = other._size;
            cap = other.cap;
            data = new T[cap];
            for (size_t i = 0; i < _size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
~Vector() {
        delete[] data;
    }
size_t size() const { return _size; }
T* begin() { return data; }
T* end()   { return data + _size; }

const T* begin() const { return data; }
const T* end()   const { return data + _size; }
void push_back(const T& value) {
        if (_size >= cap) {
            resize(cap == 0 ? 1 : cap * 2); 
        }
        data[_size++] = value;
    }
void erase(size_t index) {
        if (index >= _size) throw std::out_of_range("loi index");
        
        for (size_t i = index; i < _size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --_size;
    }
T& operator[](size_t index) {
        if (index >= _size) throw std::out_of_range("Loi Index");
        return data[index];
    }

const T& operator[](size_t index) const {
        if (index >= _size) throw std::out_of_range("loi index ");
        return data[index];
    }
void clear(){
    _size = 0;
}

void reserve(size_t newCap){
    if(newCap > cap){
        resize(newCap);
    }
}
};
#endif