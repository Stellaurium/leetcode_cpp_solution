//
// Created by stellaura on 02/09/24.
//

#pragma once

#include <concepts>
#include <iterator>

// 直接在原地修改
template <typename Iter, typename Func, typename Transform = std::identity>
    requires std::forward_iterator<Iter> &&
             std::is_invocable_r_v<bool, Func, typename std::iterator_traits<Iter>::value_type> &&
             std::is_invocable_r_v<typename std::iterator_traits<Iter>::value_type, Transform,
                                   typename std::iterator_traits<Iter>::value_type &>
size_t fast_and_slow_pointer(Iter begin, Iter end, Func is_movable, Transform transform = {}) {
    auto slow = begin;
    auto fast = begin;
    while (fast != end) {
        if (is_movable(*fast)) {
            *fast = transform(*fast);
            std::swap(*slow, *fast);
            slow++;
        }
        fast++;
    }
    return slow - begin;
}