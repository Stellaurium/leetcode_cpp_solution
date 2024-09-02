//
// Created by stellaura on 01/09/24.
//

#pragma once

// 不想改cmake了 用到就手动添加吧
#include "../projects/multiplicative_inverse/include/multiplicative_inverse.h"
#include <iostream>

// Rabin fingerprint
// H(T[a,b]) = \sum_{i = 0}^{b-a}T_{b-i}base^i
// 我们左侧叫做前端front 右侧叫做后端back
template <typename T, typename HashType = int64_t>
class RollingHash {
  private:
    HashType base;
    HashType inverse_base;
    HashType modulus;
    HashType hash_value = 0;
    // 维护一个变量 一直是最左侧的数字的 base^length 值
    HashType front_base_value;

  public:
    RollingHash(HashType base_, HashType modulus_) : base(base_), modulus(modulus_) {
        inverse_base = multiplicative_inverse::extended_gcd(modulus, base);
        // 添加一个之后才成为1
        front_base_value = inverse_base;
    }

    void push_front(T c) {
        hash_value = (hash_value * base + c) % modulus;
        front_base_value = (front_base_value * base) % modulus;
    }

    void pop_front(T c) {
        hash_value = (hash_value - c) * inverse_base % modulus;
        front_base_value = (front_base_value * inverse_base) % modulus;
    }

    void push_back(T c) {
        front_base_value = (front_base_value * base) % modulus;
        hash_value = (hash_value + c * front_base_value) % modulus;
    }

    void pop_back(T c) {
        hash_value = (hash_value - c * front_base_value) % modulus;
        front_base_value = (front_base_value * inverse_base) % modulus;
    }

    HashType get_hash() const { return hash_value; }
};

template <typename T, typename HashType = int64_t>
class RollingHashWithString{
  private:
    std::string s;
    RollingHash<T, HashType> rh;
    int begin = 0;
    // 不包含这个end
    int end = 0;
  public:

    template <typename Str>
    requires std::is_same_v<std::decay_t<Str>, std::string>
    RollingHashWithString(Str&& s_, HashType base_, HashType modulus_) : s(s_), rh(base_, modulus_) {}

    void front_go_forward(){
        rh.pop_front(s[begin++]);
    }
    void front_go_backward(){
        rh.push_front(s[--begin]);
    }
    void back_go_forward(){
        rh.push_back(s[end++]);
    }
    void back_go_backward(){
        rh.pop_back(s[--end]);
    }
    HashType get_hash() const { return rh.get_hash(); }
};
