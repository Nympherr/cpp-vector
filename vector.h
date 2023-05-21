#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>


template <typename T>
class Vector{

    public:

    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;

    size_type size() const { return vectorLimit - vectorData; }
    T& operator[](size_type index) { return vectorData[index];}
    const T& operator[](size_type index) const { return vectorData[index];}

    iterator begin() { return vectorData; } 
    const_iterator begin() const { return vectorData; } 
    iterator end() { return vectorLimit; } 
    const_iterator end() const { return vectorLimit; } 

    // konstruktoriai
    Vector(){ createVector(); }
    explicit Vector(size_type number, const T& value = T{}) { createVector(number, value); }

    // copy konstruktorius
    Vector(const Vector& vector) { createVector(vector.begin(), vector.end()); }

    // priskyrimo operatorius
    Vector& operator=(const Vector& other) {
        if(this != &other) {
            uncreate();
            createVector(other.begin(), other.end());
        }
        return *this;
    }

    ~Vector() { uncreate(); }

    void createVector(){
        vectorData = nullptr;
        vectorLimit = nullptr;
    }
    void createVector(size_type number, const T& value = T{}){
        vectorData = new T[number];
        vectorLimit = vectorData + number;
        for(size_type i = 0; i < number; i++) {
        vectorData[i] = value;
        }
    }
    void createVector(const_iterator start, const_iterator end){
        size_type size = end - start;
        vectorData = new T[size];
        std::copy(start, end, vectorData);
        vectorLimit = vectorData + size;
    }
    void uncreate(){
        if(vectorData){
            delete[] vectorData;
            vectorData = nullptr;
            vectorLimit = nullptr;
        }
    }
        private:

        iterator vectorData;
        iterator vectorLimit;

};


#endif