# AA_24_10_search_algorithms
Домашняя работа группы АА-24-10. Состав команды: Измаилов Артём, Авадаев Виталий, Мова Вячеслав, Закревский Кирилл, Литвинов Семён, Мягков Матвей. Поиск текста в файле.

## СТРУКТУРА
search_project/                           
├── main.cpp                              # Основной файл с системой тестирования
├── search_race.h                         # Общие структуры данных и типы
├── utils.h                               # Вспомогательные функции
├── algorithms/                           # Папка для алгоритмов поиска
│   ├── kmp_by_author_.h                  # name_by_author.h
│   ├── boyer_moore_by_author.h
│   └── ...
├── datasets/                             # Тестовые файлы для поиска
│   ├── data1.txt
│   └── ...
└── results/                              # папка с результатами
    └── ... (создается автоматически)


1. Создание файла алгоритма
Создайте новый файл в папке algorithms/ с именем название_алгоритма_by_ваше_имя.h

2. Структура алгоритма
Каждый алгоритм должен иметь следующую структуру:
    ```bash
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
    ```bash
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