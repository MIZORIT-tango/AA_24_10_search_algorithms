#pragma once
#include "../search_race.h"
#include "../utils.h"
#include <vector>
#include <string>
#include <algorithm>

SearchResult rabin_karp_search(const std::string& file_path,
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

    // Константы для хеширования
    const int PRIME = 101;
    const int BASE = 256;

    // Вычисляем base^(m-1) mod prime
    long long base_power = 1;
    for (int i = 0; i < m - 1; i++) {
        base_power = (base_power * BASE) % PRIME;
    }

    // Вычисляем хеш для паттерна и первой подстроки текста
    long long pattern_hash = 0;
    long long text_hash = 0;

    for (int i = 0; i < m; i++) {
        pattern_hash = (pattern_hash * BASE + pattern[i]) % PRIME;
        text_hash = (text_hash * BASE + text[i]) % PRIME;
    }

    // Основной цикл поиска
    for (int i = 0; i <= n - m; i++) {
        // Проверяем совпадение хешей
        if (pattern_hash == text_hash) {
            // Проверяем на коллизию (посимвольное сравнение)
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                result.found = true;
                result.indices.push_back(i);
            }
        }

        // Пересчитываем хеш для следующей подстроки (если не последняя)
        if (i < n - m) {
            text_hash = (text_hash - text[i] * base_power) % PRIME;
            if (text_hash < 0) {
                text_hash += PRIME; // Обеспечиваем неотрицательность
            }
            text_hash = (text_hash * BASE + text[i + m]) % PRIME;
        }
    }

    return result;
}