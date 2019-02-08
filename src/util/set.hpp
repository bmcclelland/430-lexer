#pragma once

#include <unordered_set>

namespace lexer {

template <typename T>
using Set = std::unordered_set<T>;

template <typename T>
bool contains(Set<T> const& set, T const& key) {
    return set.count(key) > 0;
}

} //lexer
