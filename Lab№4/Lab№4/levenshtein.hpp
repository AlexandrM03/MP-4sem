#include "libs.hpp"

int levenshtein(const std::string& s1, const int len1, const std::string& s2, const int len2) {
	std::vector<std::vector<int>> d(len1 + 1, std::vector<int>(len2 + 1));

	d[0][0] = 0;
	for (size_t i = 1; i <= len1; ++i) d[i][0] = i;
	for (size_t j = 1; j <= len2; ++j) d[0][j] = j;

	for (size_t i = 1; i <= len1; ++i)
		for (size_t j = 1; j <= len2; ++j)
			d[i][j] = std::min(std::min(d[i - 1][j] + 1, d[i][j - 1] + 1),
							   d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));

	return d[len1][len2];
}

int levenshtein_recursive(const std::string& s1, const int len1, const std::string& s2, const int len2) {
	if (len1 == 0) return len2;
	if (len2 == 0) return len1;

	if (s1[len1 - 1] == s2[len2 - 1])
		return levenshtein_recursive(s1, len1 - 1, s2, len2 - 1);
	else
		return 1 + std::min(std::min(levenshtein_recursive(s1, len1 - 1, s2, len2),
									  levenshtein_recursive(s1, len1, s2, len2 - 1)),
										levenshtein_recursive(s1, len1 - 1, s2, len2 - 1));
}