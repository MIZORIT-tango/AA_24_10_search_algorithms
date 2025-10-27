#pragma once
#include "../search_race.h"
#include "../utils.h"
#include <vector>
#include <string>
#include <algorithm>

SearchResult boyer_moore_by_Mova(const std::string& file_path,
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

    const int ALPHABET_SIZE = 256;
    std::vector<int> badChar(ALPHABET_SIZE, m);

    for (int i = 0; i < m - 1; ++i) {
        badChar[static_cast<unsigned char>(pattern[i])] = m - 1 - i;
    }

    int i = 0;
    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }

        if (j < 0) {
            result.found = true;
            result.indices.push_back(i);
            if (i + m < n) {
                i += badChar[static_cast<unsigned char>(text[i + m])];
            }
            else {
                i += 1;
            }
        }
        else {
            i += std::max(1, badChar[static_cast<unsigned char>(text[i + j])] - (m - 1 - j));
        }
    }

    return result;
}