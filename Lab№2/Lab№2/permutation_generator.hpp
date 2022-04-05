#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ranges>
#include <cmath>

template<typename T> 
class PermutationsGenerator {
private:
	PermutationsGenerator() = default;

public:
	static std::vector<std::vector<T>> GeneratePermutations(std::vector<T> set) {
		std::vector<std::vector<T>> permutations;
		NextPermutation(permutations, set, 0, set.size());
		return permutations;
	}

	static void NextPermutation(std::vector<std::vector<T>>& permutations, std::vector<T> set, int begin, int size) {
		if (begin == size - 1) {
			permutations.push_back(set);
			return;
		}

		for (int i = begin; i < size; i++) {
			std::swap(set[begin], set[i]);
			NextPermutation(permutations, set, begin + 1, size);
			std::swap(set[begin], set[i]);
		}
	}

	static void ShowPermutations(std::vector<T> set) {
		std::vector<std::vector<T>> permutations = GeneratePermutations(set);
		std::string res = "Permutations = {\n";
		std::for_each(permutations.begin(), permutations.end(), [&](const auto& permutation) {
			res += "    { ";
			std::for_each(permutation.begin(), permutation.end(), [&](const auto& i) {
				res += i;
				res += ", ";
				});
			if (res.ends_with(", "))
				res = res.substr(0, res.size() - 2);
			res += " }\n";
			});
		res += "}\n\n";
		std::cout << res;
	}
};