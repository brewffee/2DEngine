#include "../../include/util/Result.h"

template <typename T>
Result<T>::Result(T value): value_(value), has_value_(true) {}

template <typename T>
Result<T>::Result(std::string error_msg): has_value_(false), error_msg_(std::move(error_msg)) {}

template <typename T>
[[nodiscard]] bool Result<T>::ok() const { return has_value_; }

template <typename T>
[[nodiscard]] T Result<T>::value() const { return value_; }

template <typename T>
T Result<T>::operator->() const { return value_; }

template <typename T>
[[nodiscard]] std::string Result<T>::error() const {
    if (has_value_) return "All good!";
    return error_msg_;
}
