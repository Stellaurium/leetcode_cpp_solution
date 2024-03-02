//
// Created by Stellaura on 2023/9/25.
//

#ifndef LEETCODE_HEADER_TOOLS_H_
#define LEETCODE_HEADER_TOOLS_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <random>
#include <ctime>


template<typename T>
void print_vector(std::vector<T> v) {
  std::cout << "[";
  for (auto e : v) {
	std::cout << e << ", ";
  }
  std::cout << "]" << std::endl;
}

template<typename T>
int mod(T a, T b) {
  return a - (T)(b * floor(a / (double)b));
}

template<typename T>
int gcd(T a, T b) {
  while (b != 0) {
	T temp = b;
	b = a % b;
	a = temp;
  }
  return a;
}

#endif //LEETCODE_HEADER_TOOLS_H_
