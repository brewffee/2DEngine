#pragma once

/**
 * A utility class representing a key-value pair of type K and V
 * @tparam K - The key of this pair
 * @tparam V - The value of this pair
 */
template<class K, class V>
class Pair {
    K _key{};
    V _value{};
    
    public:
        /**
         * Constructs a new Pair object that can be accessed using key() and value()
         */
        Pair(K k, V v);
        
        Pair &operator=(const Pair &other);
        Pair &operator=(Pair &&other) noexcept;
        
        bool operator!=(const Pair &other) const;
        bool operator==(const Pair &other) const;
        
        /**
         * Creates a new Pair object where the key and value swap places
         * @return The new swapped Pair
         */
        [[nodiscard]] Pair<V, K> swap() const;

        /**
         * Accesses the key of this Pair
         */
        [[nodiscard]] K key() const;
        
        /**
         * Accesses the value of this Pair
         */
        [[nodiscard]] V value() const;
};

#include "Pair.inl"
