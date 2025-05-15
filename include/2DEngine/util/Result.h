#pragma once

#include <string>

/**
 * A utility class for operations that may either fail or succeed.
 * @tparam T - The type of value to wrap
 */
template <typename T>
class Result {
        T _value;
        bool _has_value;
        std::string _error_msg;
    
    public:
        /**
         * Wraps a (successful) value in a Result container. This value can be checked with ok(),
         * and then can be accessed using value() or its properties using the -> operator. Don't
         * rely on using error() to check for errors, as there is a default 'OK' message when called
         * on a successful result.
         * @param value - The T value to wrap
         */
        explicit Result(T value);
        
        /**
         * Wraps an error message in a Result container. This error message can be checked with !ok(),
         * and can be accessed using error().
         * @param error_msg - The error message to wrap
         */
        explicit Result(std::string error_msg);
        
        /**
         * Checks if the result of the operation was successful.
         * On unsuccessful operations, check the error() message for more details.
         * @return true if a value exists, false otherwise
         */
        [[nodiscard]] bool ok() const;
        
        /**
         * Retrieves the object stored in Result.
         * @return The T value
         */
        [[nodiscard]] T value() const;
        T operator->() const;
        
        /**
         * Returns the error message associated with this operation. Will return "All good!" if
         * there is no error.
         * @return The error message, or "All good!" on success
         */
        [[nodiscard]] std::string error() const;
};

#include "Result.inl"
