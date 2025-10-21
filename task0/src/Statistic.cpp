#include "Statistic.h"

#include <algorithm>

void Statistic::addWords(const std::vector<std::string> &words) {
    for (const auto& word : words) {
        if (!word.empty()) {
            wordCount[word]++;
            totalWords++;
        }
    }
}

std::vector<std::string> Statistic::getWords() const {
    std::vector<std::string> words;
    words.reserve(wordCount.size());
    for (const auto& [word, count] : wordCount) {
        words.push_back(word);
    }
    std::sort(words.begin(), words.end(),
        [this](const std::string& a, const std::string& b) {
            return wordCount.at(a) > wordCount.at(b);
        });
    return words;
}

std::size_t Statistic::getCount(const std::string& word) {
    return wordCount[word];
}

double Statistic::getFrequency(const std::string& word) {
    double freq = 0.0;
    if (totalWords > 0) {
        freq = wordCount[word]* 100.0 / totalWords;
    }
    return freq;
}









