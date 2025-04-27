#pragma once

#define public_props public
#define private_props private
#define public_methods public
#define private_methods private

/**
 * No default behavior. Expands to "{}"
 */
#define no_default {}

/**
 * Creates a Singleton class. Must be placed at the first line
 * of the class declaration.
 */
#define CREATE_SINGLETON_CLASS(T) \
    private: \
    static T *instance_; \
    T() = default; \
    public: \
    static T *instance() { \
        if (!instance_) instance_ = new T(); \
        return instance_; \
    } \
    private:

/**
 * Creates a basic inline getter and setter for a class member
 */
#define GETTER_SETTER(t, name) \
    t get_##name() const { return this->name; } \
    void set_##name(t name_) { this->name = name_; }

/**
 * Creates a basic inline getter for a class member
 */
#define GETTER(t, name) \
    t get_##name() const { return this->name; }

/**
 * Creates a basic inline getter for a class member, returning a reference
 */
#define GETTER_REF(t, name) \
    t &get_##name() { return this->name; }

/**
 * This function uses a template parameter "T".
 */
#define TFUNC template<typename T>
