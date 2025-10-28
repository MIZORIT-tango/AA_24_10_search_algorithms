#pragma once

#include <string>
#include <vector>

#include "../search_race.h"
#include "../utils.h"

SearchResult sequential_search(const std::string& file_path, const std::string& target_word) {
    SearchResult result;
    result.found = false;
    result.indices = {};

    std::string text = utils::readFile(file_path);
    if (text.empty() || target_word.empty()) {
        return result;
    }

    size_t n = text.size();
    size_t m = target_word.size();

    if (m > n) {
        return result;
    }

    for (size_t i = 0; i <= n - m; ++i) {
        bool match = true;
        for (size_t j = 0; j < m; ++j) {
            if (text[i + j] != target_word[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            result.found = true;
            result.indices.push_back(i);
        }
    }

    return result;
}