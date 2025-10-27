#pragma once
#include "../search_race.h"
#include "../utils.h"
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> computePrefixFunction(const std::string& pattern) {
    int m = pattern.length();
    std::vector<int> pi(m, 0);

    if (m == 0) return pi;

    int k = 0;
    for (int q = 1; q < m; ++q) {
        while (k > 0 && pattern[k] != pattern[q]) {
            k = pi[k - 1];
        }
        if (pattern[k] == pattern[q]) {
            k++;
        }
        pi[q] = k;
    }

    return pi;
}

SearchResult knuth_morris_pratt_search(const std::string& file_path,
    const std::string& target_word) {

    SearchResult result;
    result.found = false;
    result.indices.clear();

    std::string text = utils::readFile(file_path);
    if (text.empty() || target_word.empty()) {
        return result;
    }

    const std::string& pattern = target_word;
    int n = text.length();
    int m = pattern.length();

    if (n < m) {
        return result;
    }

    std::vector<int> pi = computePrefixFunction(pattern);

    int q = 0;
    for (int i = 0; i < n; ++i) {
        while (q > 0 && pattern[q] != text[i]) {
            q = pi[q - 1];
        }

        if (pattern[q] == text[i]) {
            q++;
        }

        if (q == m) {
            result.found = true;
            result.indices.push_back(i - m + 1);

            q = pi[q - 1];
        }
    }

    return result;
}
