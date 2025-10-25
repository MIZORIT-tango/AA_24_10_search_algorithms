#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace utils {
    std::string readFile(const std::string& file_path) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    void createDirectory(const std::string& path) {
        std::filesystem::create_directories(path);
    }

    std::string indicesToString(const std::vector<int>& indices) {
        if (indices.empty()) return "[]";

        std::string result = "[";
        for (size_t i = 0; i < indices.size(); ++i) {
            result += std::to_string(indices[i]);
            if (i < indices.size() - 1) {
                result += ", ";
            }
        }
        result += "]";
        return result;
    }
}