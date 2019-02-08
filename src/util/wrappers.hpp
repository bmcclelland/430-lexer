#pragma once

namespace lexer {

template <typename T>
class Wrapper {
    public:
        template <typename U>
        explicit Wrapper(Wrapper<U> const& other)
            : _value{ other._value }
        {}
        
        template <typename U>
        explicit Wrapper(Wrapper<U>&& other)
            : _value{ std::move(other._value) }
        {}

        explicit Wrapper(T const& value)
            : _value(value)
        {}

        explicit Wrapper(T&& value)
            : _value(std::move(value))
        {}

        operator T const& () const {
            return _value;
        }
    
     private:
        T _value;
};

#define NEW_WRAPPER(Type) \
    template <typename T> class Type : public Wrapper<T> {\
        using Wrapper<T>::Wrapper; };\
    template <typename T> Type(T const&) -> Type<T>;\
    template <typename T> Type(T&&) -> Type<T>\
/* NEW_WRAPPER */

NEW_WRAPPER(Min);
NEW_WRAPPER(Max);

} // namespace iot
