TFUNC Result<T>::Result(T value):
    value_(value),
    has_value_(true) {}

TFUNC Result<T>::Result(std::string error_msg):
    has_value_(false),
    error_msg_(std::move(error_msg)) {}

// //////////////////////////////////////////////////////////////////////////////////////////

TFUNC T Result<T>::operator->() const {
    return value_;
}

// //////////////////////////////////////////////////////////////////////////////////////////

TFUNC bool Result<T>::ok() const {
    return has_value_;
}

TFUNC T Result<T>::value() const {
    return value_;
}

TFUNC std::string Result<T>::error() const {
    if (has_value_) return "All good!";
    return error_msg_;
}
