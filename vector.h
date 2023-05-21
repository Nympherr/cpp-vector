#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <algorithm>
#include <string>
#include <memory>


template <typename T>
class Vector{

    public:

        typedef T* iterator;
        typedef const T* const_iterator;
        typedef size_t size_type;
        typedef T value_type;

        // rule of three
        Vector(){ createVector(); }

        explicit Vector(size_type number, const T& value = T{}) { createVector(number, value); vectorAvailable = vectorData + number;  }

        Vector(const Vector& vector) { createVector(vector.begin(), vector.end()); }

        Vector& operator=(const Vector& other) {
            if(this != &other) {
                uncreate();

                vectorData = alloc.allocate(other.size());
                vectorLimit = vectorData + other.size();
                vectorAvailable = std::uninitialized_copy(other.begin(), other.end(), vectorData);
            }
            return *this;
        }

        ~Vector() { uncreate(); }

        // operatorių overloadinimas
        T& operator[](size_type index) { return vectorData[index];}
        const T& operator[](size_type index) const { return vectorData[index];}

        // setteriai
        void push_back(const T& value){
            if(vectorAvailable == vectorLimit){
                grow();
            }
            unchecked_append(value);
        }

        void pop_back(){
            if(vectorAvailable != vectorData){
                alloc.destroy(--vectorAvailable);
            }
        }

        bool empty() const { return vectorData == vectorAvailable; }

        void reserve(size_type number){
            if(number > capacity()){
                iterator new_data = alloc.allocate(number);
                iterator new_available = std::uninitialized_copy(vectorData, vectorAvailable, new_data);
                uncreate();
                vectorData = new_data;
                vectorAvailable = new_available;
                vectorLimit = vectorData + number;
            }
        }

        void resize(size_type number){
            if(number > capacity()){
                reserve(number);
            }
            if(number > size()){
                std::uninitialized_fill(vectorAvailable, vectorData + number, T{});
            }
            else if(number < size()){
                while(vectorAvailable != vectorData + number){
                    alloc.destroy(--vectorAvailable);
                }
            }
            vectorAvailable = vectorData + number;
        }

        void clear(){
            while(vectorAvailable != vectorData){
                alloc.destroy(--vectorAvailable);
            }
        }

        void print(){
            
            if(size() == 0){
                std::cout << "Vector is empty!";
            }
            else{
                for(int i = 0; i < size(); i++){
                    std::cout << vectorData[i] << " ";
                }
                std::cout << std::endl;
            }
        }

        void erase(iterator position){
            if(position + 1 != vectorAvailable){
                std::copy(position + 1, vectorAvailable, position);
            }
            alloc.destroy(--vectorAvailable);
        }
        void erase(size_type position){
            iterator index = begin() + position;
            if(index + 1 != vectorAvailable){
                std::copy(index + 1, vectorAvailable, index);
            }
            alloc.destroy(--vectorAvailable);
        }
        void erase(iterator first_position, iterator last_position){
            iterator index = std::copy(last_position, vectorAvailable, first_position);
            while(index != vectorAvailable){
                alloc.destroy(--vectorAvailable);
            }
        }
        void erase(size_type start_position, size_type last_position){

            iterator index_start = begin() + start_position;
            iterator index_end = begin() + last_position;
            iterator index = std::copy(index_end, vectorAvailable, index_start);
            while(index != vectorAvailable){
                alloc.destroy(--vectorAvailable);
            }
        }

        // getteriai
        size_type capacity() const { return vectorLimit - vectorData; }
        size_type size() const { return vectorAvailable - vectorData; }
        iterator begin() { return vectorData; } 
        const_iterator begin() const { return vectorData; } 
        iterator end() { return vectorAvailable; } 
        const_iterator end() const { return vectorAvailable; } 

    private:

        iterator vectorData;
        iterator vectorAvailable;
        iterator vectorLimit;
        std::allocator<T> alloc; 

        // pagalbinės funkcijos
        void createVector(){
            vectorData = vectorLimit = vectorAvailable = nullptr;
        }

        void createVector(size_type number, const T& value = T{}){
            vectorData = alloc.allocate(number);
            vectorAvailable = vectorLimit = vectorData + number;
            std::uninitialized_fill_n(vectorData, number, value);
        }

        void createVector(const_iterator start, const_iterator end){
            vectorData = alloc.allocate(end - start);
            vectorAvailable = std::uninitialized_copy(start, end, vectorData);
            vectorLimit = vectorData + (end - start);
        }
                
        void uncreate(){
            if(vectorData){
                for (iterator p = vectorAvailable; p != vectorData; )
                    alloc.destroy(--p);
                    alloc.deallocate(vectorData, vectorLimit - vectorData);
                    vectorData = vectorAvailable = vectorLimit = nullptr;
            }
        }
                
        void grow(){
            size_type new_size = std::max(2 * (vectorLimit - vectorData), ptrdiff_t(1));
            iterator new_data = alloc.allocate(new_size);
            iterator new_available = new_data + (vectorAvailable - vectorData);
            std::uninitialized_copy(vectorData, vectorAvailable, new_data);
            uncreate();
            vectorData = new_data;
            vectorAvailable = new_available;
            vectorLimit = vectorData + new_size;
        }
             
        void unchecked_append(const T& value){
            alloc.construct(vectorAvailable++, value);
        }
};


#endif