#pragma once

#include <cstdlib>
#include <initializer_list>
#include <array>
#include <stdexcept>
#include "Result.h"
#include "../macros.h"

/**
 * A class representing a dynamic array of objects. Most operations return a
 * pointer to the existing vector, so methods can be chained together. Do note
 * that vector operations are made in-place, so if you do not want to modify
 * the original vector, make a copy using the copy() method.
 *
 * @tparam T - The type of object to store
 */
template <typename T>
class Vector {
    T* _data{};
    size_t _size;
    size_t _capacity;
    
    void resize(size_t new_capacity);
    
    public:
        Vector();
        Vector(std::initializer_list<T> list);
        Vector(const Vector &other);
        Vector(Vector &&other) noexcept;
        explicit Vector(size_t initial_capacity);
        ~Vector();
        
        Vector &operator=(const Vector &other);
        Vector &operator=(Vector &&other) noexcept;
        T &operator[](size_t index) const;
        
        [[nodiscard]] size_t size() const;
        [[nodiscard]] size_t capacity() const;
        [[nodiscard]] T *data() const;
        
        [[nodiscard]] T *begin() const;
        [[nodiscard]] T *end() const;
        
        /**
         * Gets the value at the specified index
         * @param index - The index of the value
         * @exception std::out_of_range - if the index is greater than the size of the vector
         */
        [[nodiscard]] T &at(size_t index) const;
        
        /**
         * Gets the last value in the vector.
         * @exception std::out_of_range - if the vector is empty
         */
        [[nodiscard]] T &back() const;
        
        /**
         * Deletes everything in the vector
         * @return - The resulting empty vector
         */
        Vector<T> clear();
        
        /**
         * Creates a copy of this vector
         * @return - A newly created Vector
         */
        [[nodiscard]] Vector<T> copy() const;
        
        /**
         * Determines whether the vector contains the specified value
         * @param value - The value to search for
         * @return - true if the value is found, false otherwise
         */
        [[nodiscard]] bool contains(const T &value) const;
        
        /**
         * Checks if the vector contains no values
         * @return - true if the vector is empty, false otherwise
         */
        [[nodiscard]] bool empty() const;
        
        /**
         * Removes the item at the specified index
         * @param index - The index of the item to remove
         * @return - The
         */
        Vector<T> erase(size_t index);
        
        /**
         * Function pointer type for Vector::filter's callback parameter. This function passes a const reference
         * to the item and should return true if the item should be kept, false if not.
         */
        using FilterCondition = bool(*)(const T &item);
        
        /**
         * Filters the vector in place using the specified callback function
         * @param condition - The callback to use when filtering items. It should have the following signature:
         * @code
         *  bool my_function(const T &item);
         * @endcode
         *
         * @return - The filtered vector
         */
        Vector<T> filter(FilterCondition condition);
        
        /**
         * Floods the vector with the specified value from specified start to end index.
         * @param value - The new value
         * @param start - The start index
         * @param end - The end index
         * @return - The resulting vector
         */
        Vector<T> flood(const T &value, size_t start, size_t end);
        
        /**
         * Function pointer type for iterating over the vector. This function passes a reference to the item and
         * should not return anything.
         */
        using ItemCallback = void(*)(T &item);
        
        /**
         * Iterates over the vector using the specified callback function
         * @param callback - The callback to use when iterating over items. It should have the following signature:
         * @code
         *  void my_function(T &item);
         * @endcode
         */
        void for_each(ItemCallback callback);
        
        /**
         * Gets the first item in the vector
         * @exception std::out_of_range - if the vector is empty
         */
        [[nodiscard]] T &front() const;
        
        /**
         * Gets the index of the first occurrence of the specified value.
         * @param value - The value to search for
         * @return a Result object containing the index if successful, or an error message if not.
         */
        [[nodiscard]] Result<size_t> index_of(const T &value) const;
        
        /**
         * Gets the indexes of all occurrences of the specified value.
         * @param value - The value to search for
         * @return a Vector object containing the indexes. If the value is not found, an empty vector is returned
         */
        [[nodiscard]] Vector<size_t> indexes_of(const T &value) const;
        
        /**
         * Inserts a new item at the specified index
         * @param index - Where to insert the new item
         * @param value - The value to insert
         * @return - The resulting vector
         */
        Vector<T> insert(size_t index, const T &value);
        
        /**
         * Replaces the value at the specified index
         * @param index - The index of the value to replace
         * @param value - The new value
         * @return - The resulting vector
         */
        Vector<T> replace(size_t index, const T &value);
        
        /**
         * Merges another vector into this vector
         * @param other - The vector to source values from
         * @return - The resulting vector
         */
        Vector<T> merge(const Vector<T> &other);
        
        /**
         * Merges another vector into this vector, placing items at the front in the sameb order as they were
         * in the source vector
         * @param other - The vector to source values from
         * @return - The resulting vector
         */
        Vector<T> merge_front(const Vector<T> &other);
        
        /**
         * Removes the last item in the vector
         */
        void pop_back();
        
        /**
         * Removes the first item in the vector
         */
        void pop_front();
        
        /**
         * Appends the specified value to the end of the vector
         * @param value - The value to append
         */
        void push_back(const T &value);
        
        /**
         * Appends the specified value to the front of the vector
         * @param value - The value to append
         */
        void push_front(const T &value);
        
        /**
         * Allocates memory for the specified capacity
         * @param new_capacity - The new capacity
         */
        void reserve(size_t new_capacity);
        
        /**
         * Reverses the order of the items in the vector
         * @return - The reversed vector
         */
        Vector<T> reverse();
        
        /**
         * Function pointer type for comparing two items. This function passes two references to the items and
         * returns true if the first item should come before the second item.
         */
        using Comparator = bool(*)(const T &a, const T &b);
        
        /**
         * Sorts the vector using the specified comparator function
         * @param comparator - The comparator function. It should have the following signature:
         * @code
         *  bool my_comparator(const T &a, const T &b);
         * @endcode
         * @return - The sorted vector
         */
        Vector<T> sort(Comparator comparator);
        
        /**
         * Shuffles the items in the vector using a random number generator.
         * todo: allow seeding
         * @return - The shuffled vector
         */
        Vector<T> shuffle();
        
        /**
         * Creates a new vector containing a slice of the original vector
         * @param start - The start index
         * @param end - The end index
         * @return - The new vector
         */
        Vector<T> slice(size_t start, size_t end);
        
        /**
         * Function pointer type for checking if an item passes a condition. This function passes a reference
         * to the item and should return true if the item passes the condition.
         */
        using PassCondition = bool(*)(const T &item);
        
        /**
         * Checks if any of the items in the vector pass the specified condition
         * @param condition - The condition to check. It should have the following signature:
         * @code
         *  bool my_condition(const T &item);
         * @endcode
         * @return - True if any items pass the condition, false if not
         */
        bool some(PassCondition condition) const;
        
        /**
         * Checks if more than half of the items in the vector pass the specified condition
         * @param condition  The condition to check. It should have the following signature:
         * @code
         *  bool my_condition(const T &item);
         * @endcode
         * @return - True if more than half of the items pass the condition, false if not
         */
        bool most(PassCondition condition) const;
        
        /**
         * Checks if all of the items in the vector pass the specified condition
         * @param condition - The condition to check. It should have the following signature:
         * @code
         *  bool my_condition(const T &item);
         * @endcode
         * @return - True if all of the items pass the condition, false if not
         */
        bool every(PassCondition condition) const;
        
        /**
         * Returns a new vector containing only the unique items in the original vector
         * @return - The new vector
         */
        Vector<T> unique();
};

#include "Vector.inl"
