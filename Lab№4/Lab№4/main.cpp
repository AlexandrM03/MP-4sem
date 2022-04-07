#include "random_string.hpp"
#include "levenshtein.hpp"
#include "subsequence.hpp"

int main() {
	// task 1
	std::string s1 = random_string(13);
	std::string s2 = random_string(15);
	std::cout << "First string: " << s1 << "\n\n";
	std::cout << "Second string: " << s2 << "\n\n";
	
	// task 2
	//std::vector<int> s1_size { 12, 15, 20, 30, 60, 150, 300 };
	//std::vector<int> s2_size { 10, 13, 17, 25, 50, 125, 250 };
	std::vector<int> s1_size { 1, 3, 5, 7, 9, 11, 13 };
	std::vector<int> s2_size { 1, 3, 6, 8, 11, 13, 15 };
	
	std::cout << std::setw(7) << "size" << std::setw(15) << "dynamic" << std::setw(15) << "recursive" << std::endl;
	std::cout << std::string(40, '-') << std::endl;

	for (size_t i = 0; i < 7; ++i) {
		const auto start_time = std::chrono::system_clock::now();
		levenshtein(s1, s1_size[i], s2, s2_size[i]);
		const auto end_time = std::chrono::system_clock::now();
		const std::chrono::duration<double> s1_diff = end_time - start_time;

		int s2_time = std::numeric_limits<int>::max();
		if (i < 4) {
			const auto start_time2 = std::chrono::system_clock::now();
			levenshtein_recursive(s1, s1_size[i], s2, s2_size[i]);
			const auto end_time2 = std::chrono::system_clock::now();
			const std::chrono::duration<double> s2_diff = end_time2 - start_time2;
			s2_time = std::chrono::duration_cast<std::chrono::milliseconds>(s2_diff).count();
		} 		
		
		std::cout << std::right << std::setw(4) << s1_size[i] << "/" << std::left << std::setw(3) << s2_size[i] 
			<< std::setw(10) << std::right << std::chrono::duration_cast<std::chrono::milliseconds>(s1_diff).count() 
			<< std::setw(15) << (s2_time == std::numeric_limits<int>::max() ? "-" : std::to_string(s2_time)) << std::endl;
	}

	// task 4
	std::string t4_1 = "Вол";
	std::string t4_2 = "Колун";
	std::cout << "\nTask 4: " << levenshtein(t4_1, t4_1.size(), t4_2, t4_2.size()) << std::endl;

	// task 5
	std::string t1 = "TBHDSAV";
	std::string t2 = "KIBYSV";
	std::cout << "\nString are: " << t1 << " and " << t2 << std::endl;
	
	const auto start_time_t1 = std::chrono::system_clock::now();
	std::cout << "Dynamic subsequence: " << lcs_dynamic(t1, t2);
	const auto end_time_t1 = std::chrono::system_clock::now();
	const std::chrono::duration<double> t1_diff = end_time_t1 - start_time_t1;
	std::cout << ", duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(t1_diff).count() << " ms" << std::endl;
	
	const auto start_time_t2 = std::chrono::system_clock::now();
	std::cout << "Recursive length: " << lcs_recursive(t1, t2, t1.size(), t2.size());
	const auto end_time_t2 = std::chrono::system_clock::now();
	const std::chrono::duration<double> t2_diff = end_time_t2 - start_time_t2;
	std::cout << ", duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2_diff).count() << " ms" << std::endl;

	return 0;
}