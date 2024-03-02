//
// Created by Stellaura on 2023/10/12.
//

#ifndef LEETCODE_SET_H_
#define LEETCODE_SET_H_

#include <memory>
// 提供std::hash函数
// 返回 size_t 类型的哈希值
#include <functional>
#include <random>
#include <cstdlib>
#include <ctime>

template<typename T>
class Node {
  public:
    T value_;
    //  如果node是nullptr 那么就是根本没有插入这个元素
    // 如果node的 is_activated_ 为 false 那么证明这个被删除了
    bool is_activated_;

    explicit Node(T value) : value_(value), is_activated_(true) {};
};

// 做一个开放寻址的map
template<typename T>
class Set {
  private:
    size_t min_size = 4;
    //  总共的数组大小
    size_t current_all_size;
    //  算上活着的元素和死人
    size_t current_non_null_size;
    //  只算活人
    size_t current_alive_size;
    Node<T> **array;

    //  这个hash function完全不靠谱
    //  只能保证不一样 但是完全没有随机性 (对int的hash是恒等函数)
    std::hash<T> hash_to_size_t;
    //  hash 函数需要用到的变量们
    //  hash(key,count) = (hash1(key) + hash2(key)(odd) * count) % 2^m
    //  两个全局变量 方便O(1)得到hash的一串序列
    //  TODO 什么时候c++有协程 yield
    unsigned long long h1;
    //  奇数
    unsigned long long h2;
    unsigned long long un_mod_index;
    size_t index;
    //  实际上没必要 c++会截断的
    //<del> 需要无限长int </del>
    // BigInt 太慢了 只能用 unsigned long long 了
    // size_t 最大规定 为 2^32 远远够用
    // 就算一个元素只有8bit 也有k M G 4G内存呢
    unsigned long long big_prime;
    unsigned long long a, b; // [0,2^32)
    unsigned long long mod_number; // 2^32

    //  随机函数
    std::random_device rd;
    std::mt19937_64 generator;
    std::uniform_int_distribution<unsigned long long> distribution;

    bool if_available(size_t index) {
        if (array[index] != nullptr and array[index]->is_activated_ == true) {
            return true;
        } else {
            return false;
        }
    }

    //  将一个数字变成一个随机化的数字
    unsigned long long random_hash(unsigned long long value) {
        //      4294967296ull: 2^32
        value = value % mod_number;
        return ((a + b * value) % big_prime) % mod_number;
    }

    void initialize_hash(T value) {
        h1 = random_hash(random_hash(hash_to_size_t(value)));
        //  TODO    虽然这样不好 但是先能用再说
        h2 = random_hash(h1);
        if (h2 % 2 == 0) {
            h2 += 1;
            h2 = h2 % mod_number;
        }
        un_mod_index = h1;
        index = un_mod_index % current_all_size;
    }

    size_t hash() {
        un_mod_index = ((h2 + un_mod_index) % mod_number);
        index = un_mod_index % current_all_size;
        return index;
    }

    void copy_to_another(size_t size, size_t last_size) {
        auto new_array = array;
        array = new Node<T> *[size];
        for(int i = 0;i<size;i++){
            array[i] = nullptr;
        }
        for (int i = 0; i != last_size; i++) {
            if (new_array[i] != nullptr and new_array[i]->is_activated_ == true) {
                insert(new_array[i]->value_);
            }
        }
        delete[] new_array;
    }

    //  检测并执行shrink
    void shrink() {
        if (current_alive_size < current_all_size / 8) {
            if (current_all_size >= min_size * 2) {
                current_all_size /= 2;
                current_non_null_size = 0;
                current_alive_size = 0;
                copy_to_another(current_all_size, current_all_size * 2);
            }
        }
    };

    //  检测并执行expand
    void expand() {
        if (current_non_null_size > current_all_size / 2) {
            current_all_size *= 2;
            current_non_null_size = 0;
            current_alive_size = 0;
            copy_to_another(current_all_size, current_all_size / 2);
            //          可能清完尸体之后 发现活着的不够多了
            shrink();
        }
    }

  public:
    Set() {
        array = new Node<T> *[min_size];
        for(int i = 0;i<min_size;i++){
            array[i] = nullptr;
        }
        current_all_size = min_size;
        current_non_null_size = 0;
        current_alive_size = 0;
        mod_number = 4294967296ull;

        //      初始化随机函数
        generator = std::mt19937_64(rd());
        distribution = std::uniform_int_distribution<unsigned long long>(0, mod_number - 1);

        //      随机化 hash
        big_prime = 1592262918131449ull;
        //      虽然不够优雅 但是能用
        a = distribution(generator);
        b = distribution(generator);
    }

    ~Set() {
        delete[] array;
    }

    bool insert(T val) {
        initialize_hash(val);
        while (true) {
            if (array[index] == nullptr) {
                array[index] = new Node<T>(val);
                current_alive_size += 1;
                current_non_null_size += 1;
                expand();
                return true;
            } else if (array[index]->is_activated_ == false and array[index]->value_ == val) {
                array[index]->is_activated_ == true;
                current_alive_size += 1;
            } else if (array[index]->is_activated_ == true and array[index]->value_ == val) {
                return false;
            }
            hash();
        }

    }

    bool remove(T val) {
        initialize_hash(val);
        while (true) {
            if (array[index] == nullptr) {
                return false;
            } else if (array[index]->is_activated_ == false and array[index]->value_ == val) {
                array[index]->is_activated_ == false;
            } else if (array[index]->is_activated_ == true and array[index]->value_ == val) {
                array[index]->is_activated_ = false;
                current_alive_size -= 1;
                shrink();
                return true;
            }
            hash();
        }
    }

    T getRandom() {
        size_t test_index = distribution(generator) % current_all_size;
        while (true) {
            if (if_available(test_index)) {
                return array[test_index]->value_;
            }
            test_index = distribution(generator) % current_all_size;
        }
    }

    class Iterator {
      private:
        Node<T> **array_;
        size_t size_;
        size_t index_;

        void get_next_index() {
            while (index_ < size_ and (array_[index_] == nullptr or array_[index_]->is_activated_ == false)) {
                index_++;
            }
        }

      public:
        Iterator(Node<T> **array, size_t size, size_t index)
            : array_(array), size_(size), index_(index) {
            get_next_index();
        };

        T &operator*() {
            return array_[index_]->value_;
        }

        Iterator &operator++() {
            index_ += 1;
            get_next_index();
            return *this;
        }

        bool operator!=(const Iterator &i) {
            return index_ != i.index_;
        }
    };

    Iterator begin() {
        return Iterator(array, current_all_size, 0);
    }

    Iterator end() {
        return Iterator(array, current_all_size, current_all_size);
    }

};

#endif //LEETCODE_SET_H_