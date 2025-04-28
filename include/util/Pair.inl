KVFUNC Pair<K, V>::Pair(K k, V v):
    _key(k),
    _value(v) {}

// //////////////////////////////////////////////////////////////////////////////////////////

KVFUNC Pair<K, V> &Pair<K, V>::operator=(const Pair<K, V> &other) {
    if (this != &other) {
        _key = other._key;
        _value = other._value;
    }
    return *this;
}

KVFUNC Pair<K, V> &Pair<K, V>::operator=(Pair &&other) noexcept {
    if (this != &other) {
        _key = other._key;
        _value = other._value;
        other._key = nullptr;
        other._value = nullptr;
    }

    return *this;
}

KVFUNC bool Pair<K, V>::operator!=(const Pair<K, V> &other) const {
    return _key != other._key || _value != other._value;
}

KVFUNC bool Pair<K, V>::operator==(const Pair<K, V> &other) const {
    return _key == other._key && _value == other._value;
}

// //////////////////////////////////////////////////////////////////////////////////////////

KVFUNC Pair<V, K> Pair<K, V>::swap() const {
    return Pair<V, K>(_value, _key);
}

KVFUNC size_t Pair<K, V>::size() const {
    return sizeof(Pair<K, V>);
}

KVFUNC K Pair<K, V>::key() const {
    return _key;
}

KVFUNC V Pair<K, V>::value() const {
    return _value;
}
