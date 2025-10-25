#pragma once
#include <vector>
#include <string>
#include <functional>

struct SearchResult {
    bool found;
    std::vector<int> indices;
    float time_ms;
};

struct TextSearchTest {
    std::string dataset_name;
    std::string file_path;
    std::string target_word;
};

using WordSearcher = std::function<SearchResult(const std::string&, const std::string&)>;