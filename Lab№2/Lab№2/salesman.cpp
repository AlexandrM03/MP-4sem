#include "salesman.hpp"

int FindPath(std::vector<std::vector<int>> towns) {
	std::vector<int> cities;
	int cities_count = towns.size();
	for (const auto& i : std::ranges::views::iota(1, cities_count)) {
		cities.push_back(i + 1);
	}
	std::vector<std::vector<int>> permutations = PermutationsGenerator<int>::GeneratePermutations(cities);

	std::ranges::for_each(permutations, [&](std::vector<int>& row) {
		row.insert(row.begin(), 1);
		row.push_back(1);
		});

	int path = 0;
	int min_path = INT_MAX;
	int min_counter = 0;
	int p1 = 0;
	int p2 = 0;
	bool is_valid = true;

	for (int i = 0; i < permutations.size(); i++) {
		path = 0;
		is_valid = true;
		for (int j = 1; j < cities.size() + 2; j++) {
			p1 = permutations[i][j - 1] - 1;
			p2 = permutations[i][j] - 1;

			if (towns[p1][p2] == INF)
				is_valid = false;
			path += towns[p1][p2];
		}

		if (path < min_path && is_valid) {
			min_counter = i;
			min_path = path;
		}
	}

	std::cout << "Path: ";
	std::ranges::for_each(permutations[min_counter], [](const auto& i) {
		std::cout << i << " ";
		});
	std::cout << std::endl;
	return min_path;
}

std::vector<std::vector<int>> Fill(int size) {
	std::vector<std::vector<int>> towns;
	towns.resize(size);

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(10, 300);
	for (int i = 0; i < size; i++) {
		towns[i].resize(size);
		for (int j = 0; j < size; j++) {
			if (i == j)
				towns[i][j] = 0;
			else 
				towns[i][j] = static_cast<int>(dist(mt));
		}
	}

	std::uniform_real_distribution<float> inf(0, size);
	for (const auto& i : std::ranges::views::iota(0, 3)) {
		towns[static_cast<int>(inf(mt))][static_cast<int>(inf(mt))] = INF;
	}

	return towns;
}