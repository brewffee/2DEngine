TFUNC void Vector<T>::resize(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < _size; ++i) {
        new_data[i] = _data[i];
    }
    delete[] _data;
    _data = new_data;
    _capacity = new_capacity;
}

// //////////////////////////////////////////////////////////////////////////////////////////

TFUNC Vector<T>::Vector():
    _data(nullptr),
    _size(0),
    _capacity(0) {}


TFUNC Vector<T>::Vector(std::initializer_list<T> list) {
    _data = new T[list.size()];
    _size = list.size();
    _capacity = list.size();
    std::copy(list.begin(), list.end(), _data);
}

TFUNC Vector<T>::Vector(const Vector &other) {
    T* new_data = new T[other._capacity];
    for (size_t i = 0; i < other._size; ++i) {
        new_data[i] = other._data[i];
    }
    _data = new_data;
    _size = other._size;
    _capacity = other._capacity;
}

TFUNC Vector<T>::Vector(Vector &&other) noexcept {
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

TFUNC Vector<T>::Vector(size_t initial_capacity):
    _data(new T[initial_capacity]),
    _size(0),
    _capacity(initial_capacity) {}

TFUNC Vector<T>::~Vector() {
    delete[] _data;
}

// //////////////////////////////////////////////////////////////////////////////////////////

TFUNC Vector<T> &Vector<T>::operator=(const Vector &other) {
    if (this != &other) {
        T* new_data = new T[other._capacity];
        for (size_t i = 0; i < other._size; ++i) {
            new_data[i] = other._data[i];
        }
        delete[] _data;
        _data = new_data;
        _size = other._size;
        _capacity = other._capacity;
    }
    return *this;
}

TFUNC Vector<T> &Vector<T>::operator=(Vector &&other) noexcept {
    if (this != &other) {
        delete[] _data;
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }
    return *this;
}

TFUNC T &Vector<T>::operator[](size_t index) const {
    if (index >= _size) throw std::out_of_range("Index out of range");
    return _data[index];
}

// //////////////////////////////////////////////////////////////////////////////////////////

TFUNC size_t Vector<T>::size() const {
    return _size;
}

TFUNC size_t Vector<T>::capacity() const {
    return _capacity;
}

TFUNC T *Vector<T>::data() const {
    return _data;
}

TFUNC T *Vector<T>::begin() const {
    return _data;
}

TFUNC T *Vector<T>::end() const {
    return _data + _size;
}

// //////////////////////////////////////////////////////////////////////////////////////////

TFUNC T &Vector<T>::at(size_t index) const {
    if (index >= _size)  throw std::out_of_range("Index out of range");
    return _data[index];
}

TFUNC Vector<T> Vector<T>::clear() {
    delete[] _data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
    return *this;
}

TFUNC Vector<T> Vector<T>::copy() const {
    return Vector<T>(*this);
}

TFUNC bool Vector<T>::contains(const T &value) const {
    return index_of(value).ok();
}

TFUNC bool Vector<T>::empty() const {
    return _size == 0;
}

TFUNC Vector<T> Vector<T>::erase(size_t index) {
    if (index >= _size) throw std::out_of_range("Index out of range");
    
    for (size_t i = index; i < _size - 1; ++i) {
        _data[i] = _data[i + 1];
    }
    _size--;
    return *this;
}

TFUNC Vector<T> Vector<T>::filter(FilterCondition condition) {
    for (size_t i = 0; i < _size;) {
        if (!condition(_data[i])) erase(i);
        else ++i;
    }
    return *this;
}

TFUNC Vector<T> Vector<T>::flood(const T &value, size_t start, size_t end) {
    if (end > _size) end = _size;
    if (start > end) throw std::invalid_argument("Invalid start/end index");
    for (size_t i = start; i < end; ++i) {
        _data[i] = value;
    }
    return *this;
}

TFUNC void Vector<T>::for_each(ItemCallback callback) {
    for (size_t i = 0; i < _size; ++i) {
        callback(_data[i]);
    }
}

TFUNC Result<size_t> Vector<T>::index_of(const T &value) const {
    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] == value) return Result<size_t>(i);
    }
    
    return Result<size_t>("Could not find value"); // not found
}

TFUNC Vector<size_t> Vector<T>::indexes_of(const T &value) const {
    Vector<size_t> indexes;
    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] == value) indexes.push_back(i);
    }
    return indexes;
}

TFUNC Vector<T> Vector<T>::insert(size_t index, const T &value) {
    if (index > _size) throw std::out_of_range("Index out of range");
    if (_size == _capacity) resize(_capacity * 2);
    for (size_t i = _size; i > index; --i) {
        _data[i] = _data[i - 1];
    }
    _data[index] = value;
    _size++;
    return *this;
}

TFUNC Vector<T> Vector<T>::replace(size_t index, const T &value) {
    if (index >= _size) throw std::out_of_range("Index out of range");
    _data[index] = value;
    return *this;
}

TFUNC Vector<T> Vector<T>::merge(const Vector<T> &other) {
    for (size_t i = 0; i < other._size; ++i) {
        this -> push_back(other[i]);
    }
    return *this;
}

TFUNC Vector<T> Vector<T>::merge_front(const Vector<T> &other) {
    for (size_t i = other._size - 1; i == 0; --i) {
        this -> push_front(other[i]);
    }
    return *this;
}

TFUNC void Vector<T>::pop_back() {
    erase(_size - 1);
}

TFUNC void Vector<T>::pop_front() { erase(0); }

TFUNC void Vector<T>::push_back(const T &value) {
    insert(_size, value);
}

TFUNC void Vector<T>::push_front(const T &value) {
    insert(0, value);
}

TFUNC void Vector<T>::reserve(size_t new_capacity) {
    if (new_capacity > _capacity) {
        resize(new_capacity);
    }
}

TFUNC Vector<T> Vector<T>::reverse() {
    for (size_t i = 0; i < _size / 2; ++i) {
        T temp = _data[i];
        _data[i] = _data[_size - i - 1];
        _data[_size - i - 1] = temp;
    }
    return *this;
}

TFUNC Vector<T> Vector<T>::sort(Comparator comparator) {
    for (size_t i = 0; i < _size; ++i) {
        for (size_t j = i + 1; j < _size; ++j) {
            if (comparator(_data[i], _data[j])) {
                T temp = _data[i];
                _data[i] = _data[j];
                _data[j] = temp;
            }
        }
    }
    return *this;
}

TFUNC Vector<T> Vector<T>::shuffle() {
    for (size_t i = 0; i < _size; ++i) {
        size_t j = rand() % _size; // NOLINT(*-msc50-cpp) todo: create custom rng
        T temp = _data[i];
        _data[i] = _data[j];
        _data[j] = temp;
    }
    return *this;
}

TFUNC Vector<T> Vector<T>::slice(size_t start, size_t end) {
    if (end > _size) end = _size;
    if (start > end) throw std::invalid_argument("Invalid start/end index");
    Vector<T> slice;
    for (size_t i = start; i < end; ++i) {
        slice.push_back(_data[i]);
    }
    return slice;
}

TFUNC bool Vector<T>::some(PassCondition condition) const {
    for (size_t i = 0; i < _size; ++i) {
        if (condition(_data[i])) return true;
    }
    return false;
}

TFUNC bool Vector<T>::most(PassCondition condition) const {
    size_t passed = 0;
    size_t required = _size / 2;
    for (size_t i = 0; i <= required; ++i) {
        if (condition(_data[i])) ++passed;
        if (passed > required) return true;
    }
    return false;
}

TFUNC bool Vector<T>::every(PassCondition condition) const {
    for (size_t i = 0; i < _size; ++i) {
        if (!condition(_data[i])) return false;
    }
    return true;
}

TFUNC Vector<T> Vector<T>::unique() {
    Vector<T> unique;
    for (size_t i = 0; i < _size; ++i) {
        bool is_unique{true};
        for (size_t j = 0; j < unique._size; ++j) {
            if (_data[i] == unique._data[j]) {
                is_unique = false;
                break;
            }
        }
        
        if (is_unique) unique.push_back(_data[i]);
    }
    return unique;
}
