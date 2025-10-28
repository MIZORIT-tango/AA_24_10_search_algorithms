#pragma once
#include "../search_race.h"
#include "../utils.h"
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <cctype>

inline int levenshtein_distance(const std::string& str1, const std::string& str2) {
    int m = str1.length();
    int n = str2.length();

    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = 1 + std::min({ dp[i - 1][j],
                                        dp[i][j - 1],
                                        dp[i - 1][j - 1] });
            }
        }
    }

    return dp[m][n];
}

inline SearchResult Fuzzy_search_by_Zakrevskiy(const std::string& file_path,
    const std::string& target_word) {

    SearchResult result;
    result.found = false;
    result.indices.clear();

    std::string text = utils::readFile(file_path);
    if (text.empty()) {
        return result;
    }

    int target_len = target_word.length();

    if (text.length() < target_len) {
        return result;
    }

    int min_distance = INT_MAX;
    int best_position = -1;

    for (size_t i = 0; i <= text.length() - target_len; i++) {
        std::string substring = text.substr(i, target_len);
        int distance = levenshtein_distance(target_word, substring);

        if (distance < min_distance) {
            min_distance = distance;
            best_position = static_cast<int>(i);
        }
    }

    if (min_distance <= 1) {
        result.found = true;
        result.indices.push_back(best_position);
    }

    return result;
}