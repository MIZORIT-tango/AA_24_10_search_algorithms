# AA_24_10_search_algorithms
Домашняя работа группы АА-24-10. Состав команды: Измаилов Артём, Авадаев Виталий, Мова Вячеслав, Закревский Кирилл, Литвинов Семён, Мягков Матвей. Поиск текста в файле.

## СТРУКТУРА
search_project/<br>
├── main.cpp     # Основной файл с системой тестирования <br>
├── search_race.h    # Общие структуры данных и типы<br>
├── utils.h          # Вспомогательные функции<br>
├── algorithms/      # Папка для алгоритмов поиска<br>
│   ├── kmp_by_author_.h   # name_by_author.h<br>
│   ├── boyer_moore_by_author.h<br>
│   └── ...<br>
├── datasets/        # Тестовые файлы для поиска<br>
│   ├── data1.txt<br>
│   └── ...<br>
└── results/         # папка с результатами<br>
    └── ... (создается автоматически)<br>


1. Создание файла алгоритма
Создайте новый файл в папке algorithms/ с именем название_алгоритма_by_ваше_имя.h

2. Структура алгоритма
Каждый алгоритм должен иметь следующую структуру:
    ```cpp
    #pragma once
    #include "../search_race.h"
    #include "../utils.h"
    #include <vector>
    #include <string>

    SearchResult название_алгоритма(const std::string& file_path, 
                                   const std::string& target_word) {
    
        SearchResult result;
        result.found = false;
        result.indices.clear();
    
        // Чтение файла
        std::string text = utils::readFile(file_path);
        if (text.empty()) {
            return result;
        }
    
        // Реализация вашего алгоритма поиска
        // ...
    
        return result;
    }
    ```

3. Пример готового алгоритма
    ```cpp
        // algorithms/linear_search.h
    #pragma once
    #include "../search_race.h"
    #include "../utils.h"
    #include <vector>
    #include <string>

    SearchResult linear_search(const std::string& file_path, 
                             const std::string& target_word) {
    
        SearchResult result;
        result.found = false;
    
        std::string text = utils::readFile(file_path);
        if (text.empty()) {
            return result;
        }
    
        // Реализация линейного поиска
        size_t pos = text.find(target_word);
        while (pos != std::string::npos) {
            result.found = true;
            result.indices.push_back(static_cast<int>(pos));
            pos = text.find(target_word, pos + 1);
        }
    
        return result;
    }
    ```

## Требования к алгоритмам
Функция должна возвращать SearchResult

Функция должна принимать два параметра: file_path и target_word

Использовать utils::readFile() для чтения файлов

Корректно заполнять поля found и indices

Не использовать вывод в консоль (cout)
