//
// Created by Stellaura on 2023/10/12.
//
#include "tools.h"
#include "Set.h"
#include "BigInt.hpp"
#include <iostream>
#include <functional>
#include <vector>
#include <iterator>
#include <random>
#include <limits>
#include <chrono>

int main() {
	auto start = std::chrono::high_resolution_clock::now();

	auto m = Set_with_BigInt_and_unique_ptr<int>();
	for (int i = 1; i <= 2 * 100; i++) {
		m.insert(i);
	}
//	for(auto e : m){
//		std::cout << e << " ";
//	}
//	std::cout << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "执行时间: " << duration.count() << " 微秒" << std::endl;
	return 0;
}
