#pragma once

#include <cstdlib>
#include <initializer_list>
#include <array>
#include <stdexcept>

template <typename T>
class Vector {
    T* _data;
    size_t _size;
    size_t _capacity;
    
    void resize(size_t new_size);
    
    public:
        Vector();
        Vector(std::initializer_list<T> l);
        Vector(const Vector &other);
        Vector(Vector &&other) noexcept;
        explicit Vector(size_t starting_capacity);
        ~Vector();
        
        Vector &operator=(const Vector &other);
        Vector &operator=(Vector &&other) noexcept;
        T &operator[](size_t index) const;
        
        [[nodiscard]] size_t size() const;
        [[nodiscard]] size_t capacity() const;
        T *data() const;
        
        T *begin() const;
        T *end() const;
        
        T &at(size_t index) const;
        Vector<T> clear();
        Vector<T> copy() const;
        bool contains(const T &value) const;
        [[nodiscard]] bool empty() const;
        Vector<T> erase(size_t index);
        
        using FilterCondition = bool(*)(const T &item);
        Vector<T> filter(FilterCondition condition);
        Vector<T> flood(const T &value, size_t start, size_t end);
        
        using ItemCallback = void(*)(T &item);
        void for_each(ItemCallback callback);
        
        long index_of(const T &value) const;
        Vector<T> indexes_of(const T &value) const;
        
        Vector<T> insert(size_t index, const T &value);
        Vector<T> replace(size_t index, const T &value);
        Vector<T> merge(const Vector<T> &other);
        Vector<T> merge_front(const Vector<T> &other);
        
        void pop_back();
        void pop_front();
        void push_back(const T &value);
        void push_front(const T &value);
        
        void reserve(size_t new_capacity);
        Vector<T> reverse();
        
        using Comparator = bool(*)(const T &a, const T &b);
        Vector<T> sort(Comparator comparator);
        
        Vector<T> shuffle();
        
        Vector<T> slice(size_t start, size_t end);
        
        using PassCondition = bool(*)(const T &item);
        bool some(PassCondition condition) const;
        bool most(PassCondition condition) const;
        bool every(PassCondition condition) const;
        
        Vector<T> unique();
};
