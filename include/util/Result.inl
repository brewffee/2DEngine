#pragma once

template<typename T> Result<T>::Result(T value):
    _value(value),
    _has_value(true) {}

template<typename T> Result<T>::Result(std::string error_msg):
    _has_value(false),
    _error_msg(std::move(error_msg)) {}

// //////////////////////////////////////////////////////////////////////////////////////////

template<typename T> T Result<T>::operator->() const {
    return _value;
}

// //////////////////////////////////////////////////////////////////////////////////////////

template<typename T> bool Result<T>::ok() const {
    return _has_value;
}

template<typename T> T Result<T>::value() const {
    return _value;
}

template<typename T> std::string Result<T>::error() const {
    if (_has_value) return "All good!";
    return _error_msg;
}
