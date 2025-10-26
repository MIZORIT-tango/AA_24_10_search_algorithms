#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include "search_race.h"
#include "utils.h"
#include "algorithms/rabina_karpa_by_Avadaev.h"


//#include "algorithms/kmp_search_by_author.h"


using namespace std;


#define RUN(x) { \
    Run(#x, x, test); \
}


static map<string, vector<string>> results_by_dataset;


SearchResult standard_search(const string& file_path, const string& target_word) {
    SearchResult result;
    result.found = false;

    string text = utils::readFile(file_path);
    if (text.empty()) return result;

    size_t pos = text.find(target_word);
    while (pos != string::npos) {
        result.found = true;
        result.indices.push_back(static_cast<int>(pos));
        pos = text.find(target_word, pos + 1);
    }

    return result;
}

void Run(string method_name, WordSearcher searcher, const TextSearchTest& test) {

    auto start = chrono::high_resolution_clock::now();
    SearchResult result = searcher(test.file_path, test.target_word);
    auto stop = chrono::high_resolution_clock::now();

    auto time_us = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    SearchResult standard_result = standard_search(test.file_path, test.target_word);
    bool is_correct = (result.found == standard_result.found);

    string indices_str = utils::indicesToString(result.indices);

    ostringstream oss;
    oss << method_name << "\t"
        << (result.found ? "true" : "false") << "\t"
        << indices_str << "\t"
        << time_us << "mcs" << "\t"
        << (is_correct ? "CORRECT" : "WRONG");

    results_by_dataset[test.dataset_name].push_back(oss.str());
}

void saveResults() {
    utils::createDirectory("results");

    for (const auto& [dataset_name, results] : results_by_dataset) {
        string filename = "results/" + dataset_name + "_results.txt";
        ofstream file(filename);

        file << "Algorithm\tFound\tIndices\tTime\tStatus" << endl;
        file << "==============================================" << endl;

        for (const auto& result_line : results) {
            file << result_line << endl;
        }

        cout << "Saved results for " << dataset_name << " to " << filename << endl;
    }
}

int main() {
    cout << "************** TEXT SEARCH RACE **************" << endl;

    utils::createDirectory("results");

    // Âõîäíûå äàòàñåòû, ñþäà âñòàâëÿòü 0)íàçâàíèå ôàéëà 1)ïóòü ê ôàéëó 2)target
    vector<TextSearchTest> tests = {
        {"test1", "datasets/test1.txt", "test"},
        //{"test", "test_data/test.txt", "anything"},
    };

    for (const auto& test : tests) {
        cout << "\nTesting dataset: " << test.dataset_name << endl;
        cout << "File: " << test.file_path << endl;
        cout << "Target word: '" << test.target_word << "'" << endl;
        RUN(rabin_karp_search);
        //RUN(kmp_search_by_author);
    }

    saveResults();

    cout << "\nAll results saved to 'results/' folder" << endl;
    return 0;
}
