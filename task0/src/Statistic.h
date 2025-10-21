#ifndef STATISTIC_H
#define STATISTIC_H

#include <map>
#include <string>
#include <vector>

class Statistic{
private:
    std:: size_t totalWords = 0;
    std::map<std::string, std::size_t> wordCount;

public:
    void addWords(const std::vector<std::string> &words);
    std::vector<std::string> getWords() const;
    std::size_t getCount(const std::string& word);
    double getFrequency(const std::string& word);
};

#endif