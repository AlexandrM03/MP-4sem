#pragma once
#include "subset_generator.hpp"

template<typename T>

class CombinationsGenerator {
private:
	CombinationsGenerator() = default;

public:
	static std::vector<std::vector<T>> GenerateCombinations(std::vector<T> set, int k) {
		std::vector<std::vector<T>> combinations;
		std::vector<std::vector<T>> subsets = SubsetGenerator<T>::GenerateSubsets(set);
		std::ranges::for_each(subsets, [&](const auto& subset) {
			if (subset.size() == k)
				combinations.push_back(subset);
			});

		return combinations;
	}

	static void ShowCombinations(std::vector<T> set, int k) {
		std::vector<std::vector<T>> combinations = GenerateCombinations(set, k);
		std::string res = "Combinations = {\n";
		std::for_each(combinations.begin(), combinations.end(), [&](const auto& combination) {
			res += "    { ";
			std::for_each(combination.begin(), combination.end(), [&](const auto& i) {
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