#pragma once
#include "subset_generator.hpp"
#include "permutation_generator.hpp"

template<typename T>

class PlacementGenerator {
private:
	PlacementGenerator() = default;

public:
	static std::vector<std::vector<T>> GeneratePlacements(std::vector<T> set, int k) {
		std::vector<std::vector<T>> placements;
		int set_size = set.size();
		for (const auto& i : std::ranges::views::iota(0, std::pow(set_size, 2))) {
			std::vector<bool> bits(SubsetGenerator<T>::BitsGenerator(i, set_size));
			std::vector<T> subset(SubsetGenerator<T>::SubsetsFromBits(set, bits));
			if (subset.size() == k) {
				std::vector<std::vector<T>> permutations(PermutationsGenerator<T>::GeneratePermutations(subset));
				placements.insert(placements.end(), permutations.begin(), permutations.end());
			}
		}

		return placements;
	}

	static void ShowPlacements(std::vector<T> set, int k) {
		std::vector<std::vector<T>> placements = GeneratePlacements(set, k);
		std::string res = "Placements = {\n";
		std::for_each(placements.begin(), placements.end(), [&](const auto& placement) {
			res += "    { ";
			std::for_each(placement.begin(), placement.end(), [&](const auto& i) {
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