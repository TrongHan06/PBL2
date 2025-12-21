#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <utility>  

template <typename T>
class Vector {
private:
    T* data;     
    size_t _size;      
    size_t cap; 

    void resize(size_t newCapacity) {
        if (newCapacity < _size) newCapacity = _size; 

    
        T* newData = new T[newCapacity];
    
        for (size_t i = 0; i < _size; ++i) {
            newData[i] = std::move(data[i]);  
        }

        delete[] data;
        data = newData;
        cap = newCapacity;
    }

public:

    Vector(size_t firstCap = 4) : _size(0), cap(firstCap) {
        data = new T[cap];
    }


    Vector(const Vector& other) : _size(other._size), cap(other.cap) {
        data = new T[cap];
        for (size_t i = 0; i < _size; ++i) {
            data[i] = other.data[i];
        }
    }

    Vector(Vector&& other) noexcept : data(other.data), _size(other._size), cap(other.cap) {
        other.data = nullptr;
        other._size = 0;
        other.cap = 0;
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

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            _size = other._size;
            cap = other.cap;
            other.data = nullptr;
            other._size = 0;
            other.cap = 0;
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
    const T* end() const { return data + _size; }

   
    void push_back(const T& value) {
        if (_size >= cap) {
            resize(cap == 0 ? 1 : cap * 2); 
        }
        data[_size++] = value;
    }
    void push_back(T&& value) {
        if (_size >= cap) {
            resize(cap == 0 ? 1 : cap * 2); 
        }
        data[_size++] = std::move(value);
    }

    void erase(size_t index) {
        if (index >= _size) throw std::out_of_range("loi index");
        
        for (size_t i = index; i < _size - 1; ++i) {
            data[i] = std::move(data[i + 1]); 
        }
        --_size;
    }

    T& operator[](size_t index) {
        if (index >= _size) throw std::out_of_range("Loi Index");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= _size) throw std::out_of_range("loi index");
        return data[index];
    }

    void clear() {
        _size = 0;  
    }

    void reserve(size_t newCap) {
        if (newCap > cap) {
            resize(newCap);
        }
    }
};
#endif