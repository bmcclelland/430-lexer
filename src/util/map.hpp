#pragma once

#include "result.hpp"
#include "memory.hpp"
#include <unordered_map>
#include <utility>

namespace lexer {

template <typename K, typename V>
using Map = std::unordered_map<K,V>;

template <typename K, typename V>
Optional<V> lookup(Map<K,V> const& map, K const& key) {
    auto it = map.find(key);

    // Have to be explicit here. Optional<any> didn't work.
    if (it == map.end()) {
        return Optional<V>(outcome::in_place_type_t<Fail>());
    }
    else {
        return Optional<V>(outcome::in_place_type_t<V>(), it->second);
    }
}

template <typename K, typename V>
Optional<V*> lookup(Map<K,UniquePtr<V>>& map, K const& key) {
    auto it = map.find(key);

    if (it == map.end()) {
        return failure;
    }
    else {
        return it->second.get();
    }
}

} //lexer
