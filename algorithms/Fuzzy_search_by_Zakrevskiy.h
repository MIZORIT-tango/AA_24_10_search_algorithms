#pragma once
#include "../search_race.h"
#include "../utils.h"
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

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

SearchResult fuzzy_levenshtein(const std::string& file_path,
    const std::string& target_word) {

    SearchResult result;
    result.found = false;
    result.indices.clear();

    std::string text = utils::readFile(file_path);
    if (text.empty()) {
        return result;
    }

    std::vector<std::string> words;
    std::string current_word;

    for (char c : text) {
        if (std::isalpha(c) || std::isdigit(c)) {
            current_word += c;
        }
        else {
            if (!current_word.empty()) {
                words.push_back(current_word);
                current_word.clear();
            }
        }
    }

    if (!current_word.empty()) {
        words.push_back(current_word);
    }

    int min_distance = INT_MAX;
    std::string best_match;
    size_t best_index = 0;

    for (size_t i = 0; i < words.size(); i++) {
        int distance = levenshtein_distance(target_word, words[i]);
        if (distance < min_distance) {
            min_distance = distance;
            best_match = words[i];
            best_index = i;
        }
    }

    if (min_distance <= 3) { // схожесть по умолчанию 3 символа
        result.found = true;
        result.indices.push_back(best_index);
    }

    return result;
}