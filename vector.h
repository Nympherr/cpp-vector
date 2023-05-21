#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <memory>
#include <algorithm>

template <typename T>
class Vector{

    public:

        typedef T* iterator;
        typedef const T* const_iterator;
        typedef size_t size_type;
        typedef T value_type;

        // rule of five
        Vector(){ createVector(); }

        Vector(std::initializer_list<T> initList) {
            createVector(initList.begin(), initList.end());
        }

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

        Vector& operator=(Vector&& other) noexcept {
            if (&other == this)
                return *this;

            if (vectorData) {
                alloc.deallocate(vectorData, capacity());
            }

            vectorData = other.vectorData;
            vectorAvailable = other.vectorAvailable;
            vectorLimit = other.vectorLimit;

            other.vectorData = other.vectorAvailable = other.vectorLimit = nullptr;

            return *this;
        }
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

        void shrink_to_fit(){
            iterator new_data = alloc.allocate(size());
            iterator new_available = std::uninitialized_copy(vectorData, vectorAvailable, new_data);
            uncreate();
            vectorData = new_data;
            vectorAvailable = new_available;
            vectorLimit = vectorData + size();
        }

        void insert(iterator position, const T& value){
            if (position < begin() || position > end()) {
                std::cout << ("Invalid insert position") << std::endl;
            }
            else{
                size_type offset = position - vectorData;
                if(vectorAvailable == vectorLimit){
                    grow();
                    position = vectorData + offset;
                }
                std::copy_backward(position, vectorAvailable, vectorAvailable + 1);
                *position = value;
                ++vectorAvailable;
            }
        }

        void insert(iterator position, iterator start, iterator finish) {
            if (position < begin() || position > end()) {
                std::cout << ("Invalid insert position") << std::endl;
            }
            else{
                size_type offset = position - vectorData;
                size_type new_elements_count = finish - start;

                if(vectorAvailable + new_elements_count > vectorLimit) {
                    grow();
                }
                else {
                    std::copy_backward(position, vectorAvailable, vectorAvailable + new_elements_count);
                    std::copy(start, finish, position);
                    vectorAvailable += new_elements_count;
                }
            }
        }

        void assign(size_type number, const T& value){
            clear();
            if(number > capacity()){
                reserve(number);
            }
            for(size_type i = 0; i < number; i++){
                push_back(value);
            }
        }

        void assign(iterator start, iterator finish){
            clear();
            if(std::distance(start, finish) > capacity()){
                reserve(std::distance(start, finish));
            }
            for(iterator i = start; i != finish; i++){
                push_back(*i);
            }
        }
        void assign(std::initializer_list<T> ilist){
            assign(ilist.begin(), ilist.end());
        }

        template<typename InputIterator>
        void assign(InputIterator first, InputIterator last) {
            clear();
            while (first != last) {
                push_back(*first);
                ++first;
            }
        }
        void swap(Vector& other){
            std::swap(vectorData, other.vectorData);
            std::swap(vectorAvailable, other.vectorAvailable);
            std::swap(vectorLimit, other.vectorLimit);
        }

        // getteriai
        size_type capacity() const { return vectorLimit - vectorData; }
        size_type size() const { return vectorAvailable - vectorData; }
        iterator begin() { return vectorData; } 
        const_iterator begin() const { return vectorData; } 
        iterator end() { return vectorAvailable; } 
        const_iterator end() const { return vectorAvailable; }
        T& front() { return *vectorData; }
        const T& front() const { return *vectorData; }
        T& back() { return *(vectorAvailable - 1); }
        const T& back() const { return *(vectorAvailable - 1); } 
        T& at(size_type index){
            if(index < 0 || index >= size()){
                throw std::out_of_range("Index out of range");
            }
            return vectorData[index];
        }
        T* data() noexcept { return vectorData; }
        const T* data() const noexcept { return vectorData; }
        const T& at(size_type index) const {
            if(index < 0 || index >= size()){
                throw std::out_of_range("Index out of range");
            }
            return vectorData[index];
        }

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
                
        void uncreate() {
            if(vectorData) {
                for (iterator p = vectorAvailable; p != vectorData; )
                    (--p)->~T();
                alloc.deallocate(vectorData, vectorLimit - vectorData);
                vectorData = vectorAvailable = vectorLimit = nullptr;
            }
        }
                
        void grow(){
            size_type new_size = std::max(10 * (vectorLimit - vectorData), ptrdiff_t(1));
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