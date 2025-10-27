#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

namespace fuzzy_search {
    int levenshtein_distance(const std::string& str1, const std::string& str2) {
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

    struct SearchResult {
        std::string word;
        int distance;
        size_t index;

        SearchResult(const std::string& w, int d, size_t idx = 0)
            : word(w), distance(d), index(idx) {
        }
    };

    std::vector<SearchResult> fuzzy_search(
        const std::string& query,
        const std::vector<std::string>& dictionary,
        int max_distance = 3) {

        std::vector<SearchResult> results;

        for (size_t i = 0; i < dictionary.size(); i++) {
            const auto& word = dictionary[i];
            int distance = levenshtein_distance(query, word);

            if (distance <= max_distance) {
                results.emplace_back(word, distance, i);
            }
        }
        std::sort(results.begin(), results.end(),
            [](const SearchResult& a, const SearchResult& b) {
                return a.distance < b.distance;
            });

        return results;
    }

    SearchResult find_best_match(
        const std::string& query,
        const std::vector<std::string>& dictionary,
        int max_distance = 3) {

        auto results = fuzzy_search(query, dictionary, max_distance);

        if (!results.empty()) {
            return results[0];
        }

        return SearchResult("", INT_MAX);
    }

}