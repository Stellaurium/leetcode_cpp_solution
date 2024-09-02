//
// Created by stellaura on 01/09/24.
//

// 主要的算法来自于
// https://oi-wiki.org/math/number-theory/inverse/

#pragma once

#include <stdexcept>



namespace _implementation {

// a，b是传入的参数，
// 不管何时 x y 满足 ax + by = gcd(a, b)
// 整个 辗转相除法 的过程中 会产生一系列数字
// 最后的两个数字是 gcd 和 0
// 因此 我们这时候可以使 x = 1, y = 0 作为初始值
// 然后只需要维持 ax + by = gcd(a, b) 性质即可
void ex_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return;
    }
    ex_gcd(b, a % b, y, x);
    // 这个函数完成之后 我们已经知道
    // b * y + a % b * x = gcd
    // 现在只需要变换
    // b * y + (a - a/b * b) * x = gcd
    // a * x + b * (y - a/b * x) = gcd
    // 现在需要维持 该函数调用时 ax + by = gcd 的性质
    y = y - a / b * x;
}

} // namespace _implementation

namespace multiplicative_inverse {

// 复杂度 log(a)
// 因为第一次一定使得 m 变得小于 a
// 因此不管m多大都对复杂度没有影响
// 之后 至少每两次 都可以至少 让 a 减半
// (可以证明 a < 2*b 的时候 两次之后 a就会减半)
// 因此 log
template <typename T>
T extended_gcd(T m, T a) {
    int x, y;
    _implementation::ex_gcd(m, a, x, y);

    if (m * x + a * y != 1) {
        throw std::invalid_argument("GCD of " + std::to_string(a) + " and " + std::to_string(m) +
                                    " is not 1, no multiplicative inverse exists.");
    }
    return (y % m + m) % m;
}

// 要求 p 是质数
// a ^ p-1 == 1 (mod p)
// 即 a * a ^ (p-2) == 1 (mod p)
// 复杂度 log(p)
template <typename T>
T quick_pow(T p, T a) {
    T ret = 1;
    a = (a % p + p) % p;
    for (T b = p - 2; b; b >>= 1) {
        if (b & 1)
            ret = (a * ret) % p;
        a = (a * a) % p;
    }
    return ret;
}

// OI WIKI 上还有 1-n 对p的逆元
// 相当的精妙

// 和 任意n个数 对p的逆元



} // namespace multiplicative_inverse
