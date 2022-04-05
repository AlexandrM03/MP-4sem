#include "libs.hpp"

std::string lcs_dynamic(std::string s1, std::string s2) {
	int n = s1.size(), m = s2.size();
	std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
	std::string res;
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (s1[i - 1] == s2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			} else {
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	
	int i = n, j = m;
	while (i > 0 && j > 0) {
		if (s1[i - 1] == s2[j - 1]) {
			res.push_back(s1[i - 1]);
			--i;
			--j;
		} else if (dp[i - 1][j] > dp[i][j - 1]) {
			--i;
		} else {
			--j;
		}
	}

	std::reverse(res.begin(), res.end());
	return res;
}

int lcs_recursive(std::string s1, std::string s2, int i, int j) {
	if (i == 0 || j == 0) 
		return 0;
	if (s1[i - 1] == s2[j - 1]) 
		return lcs_recursive(s1, s2, i - 1, j - 1) + 1;
	else 
		return std::max(lcs_recursive(s1, s2, i - 1, j), lcs_recursive(s1, s2, i, j - 1));
}