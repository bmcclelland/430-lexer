#pragma once

#include <memory>

namespace lexer {

template <typename T, typename D = std::default_delete<T>>
using UniquePtr = std::unique_ptr<T,D>;

using std::make_unique;

// OpaquePtr<T>
//  An owning pointer that can handle incomplete types.
//  Just define free_opaque_ptr(T*) somewhere.
template <typename T>
class OpaquePtr {
    public:
        OpaquePtr() = default;

        explicit OpaquePtr(T* t)
            : _t(t)
            {
        }

        ~OpaquePtr() {
            void free_opaque_ptr(T*);
            free_opaque_ptr(_t);
        }

        explicit operator bool() const {
            return _t != nullptr;
        }

        T* get() {
            return _t;
        }

        T const* get() const {
            return _t;
        }

    private:
        T* _t = nullptr;
};

} //lexer
