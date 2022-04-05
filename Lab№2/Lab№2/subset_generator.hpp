#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ranges>
#include <cmath>

template<typename T>

class SubsetGenerator {
private:
	SubsetGenerator() = default;

public:
	static std::vector<bool> BitsGenerator(int number, int bits_count) {
		std::vector<bool> bits(bits_count);
		for (int i = 0; i < bits_count; i++) {
			bits[i] = number & (1 << i);
		}

		return bits;
	}

	static std::vector<T> SubsetsFromBits(std::vector<T>& set, std::vector<bool> bits) {
		std::vector<T> subset;
		int set_size = set.size();
		for (const auto& i : std::ranges::views::iota(0, set_size)) {
			if (bits[i])
				subset.push_back(set[i]);
		}

		return subset;
	}

	static std::vector<std::vector<T>> GenerateSubsets(std::vector<T>& set) {
		std::vector<std::vector<T>> subsets;
		int set_size = set.size();
		int result_size = std::pow(set.size(), 2);
		for (const auto i : std::ranges::views::iota(0, result_size)) {
			subsets.push_back(SubsetsFromBits(set, BitsGenerator(i, set_size)));
		}

		return subsets;
	}

	static void ShowSubsets(std::vector<T> set) {
		std::vector<std::vector<T>> subsets = GenerateSubsets(set);
		std::string res = "Subsets = {\n";
		std::for_each(subsets.begin(), subsets.end(), [&](const auto& subset) {
			res += "    { ";
			std::for_each(subset.begin(), subset.end(), [&](const auto& i) {
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