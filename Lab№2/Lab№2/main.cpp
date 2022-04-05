#include "subset_generator.hpp"
#include "combination_generator.hpp"
#include "permutation_generator.hpp"
#include "placement_generator.hpp"
#include "salesman.hpp"
#include <iomanip>
#include <chrono>

int main() {
	//std::vector<char> set_char{ 'A', 'B', 'C', 'D' };
	//std::vector<int> set_int{ 1, 2, 3, 4 };
	//SubsetGenerator<char>::ShowSubsets(set_char);
	////SubsetGenerator<int>::ShowSubsets(set_int);
	//CombinationsGenerator<char>::ShowCombinations(set_char, 3);
	//PermutationsGenerator<char>::ShowPermutations(set_char);
	//PlacementGenerator<char>::ShowPlacements(set_char, 2);
	int n = 9;

	std::vector<std::vector<int>> towns = {
		{INF, 2 * n, 21 + n, INF, n},
		{n, INF, 15 + n, 68 - n, 84 - n},
		{2 + n, 3 * n, INF, 86, 49 + n},
		{17 + n, 58 - n, 4 * n, INF, 3 * n},
		{93 - n, 66 + n, 52, 13 + n, INF}
	};

	//std::vector<std::vector<int>> towns(Fill(10));
	std::for_each(towns.begin(), towns.end(), [&](const auto& city) {
		std::for_each(city.begin(), city.end(), [&](const auto& i) {
			std::cout << std::setw(10) << (i == INF ? "INF" : std::to_string(i));
			});
		std::cout << "\n\n";
		});

	const auto start_time = std::chrono::system_clock::now();
	int distance = FindPath(towns);
	const auto end_time = std::chrono::system_clock::now();
	const std::chrono::duration<double> diff = end_time - start_time;
	std::cout << "Distance: " << distance << std::endl;
	std::cout << "Duration: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() << " ms" << std::endl;
}