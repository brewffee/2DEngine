#pragma once

template<typename K, typename V>
Pair<K, V>::Pair(K k, V v):
    _key(k),
    _value(v) {}

// //////////////////////////////////////////////////////////////////////////////////////////

template<typename K, typename V>
Pair<K, V> &Pair<K, V>::operator=(const Pair &other) {
    if (this != &other) {
        _key = other._key;
        _value = other._value;
    }
    return *this;
}

template<typename K, typename V>
Pair<K, V> &Pair<K, V>::operator=(Pair &&other) noexcept {
    if (this != &other) {
        _key = other._key;
        _value = other._value;
        other._key = nullptr;
        other._value = nullptr;
    }

    return *this;
}

template<typename K, typename V>
bool Pair<K, V>::operator!=(const Pair &other) const {
    return _key != other._key || _value != other._value;
}

template<typename K, typename V>
bool Pair<K, V>::operator==(const Pair &other) const {
    return _key == other._key && _value == other._value;
}

// //////////////////////////////////////////////////////////////////////////////////////////

template<typename K, typename V>
Pair<V, K> Pair<K, V>::swap() const {
    return Pair<V, K>(_value, _key);
}

template<typename K, typename V>
K Pair<K, V>::key() const {
    return _key;
}

template<typename K, typename V>
V Pair<K, V>::value() const {
    return _value;
}
