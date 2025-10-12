#include "FileReader.h"
#include "FileWriter.h"
#include "Statistic.h"
#include "TextParser.h"

#include <iomanip>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    FileReader reader(argv[1]);
    reader.open();
    if (!reader.isOpen()) {
        std::cerr << "Can't open input file: " << argv[1] << "\n";
        return 1;
    }

    TextParser parser;
    Statistic stat;
    while (!reader.isEOF()) {
        const std::string line = reader.getLine();
        const std::vector<std::string> words = parser.parseLine(line);
        stat.addWords(words);
    }

    FileWriter writer(argv[2]);
    writer.open();
    if (!writer.isOpen()) {
        std::cerr << "Can't open output file: " << argv[2] << "\n";
        return 1;
    }

    const std::vector<std::string> uniqueWords = stat.getWords();

    for (const auto& word : uniqueWords) {
        std::ostringstream freq;
        freq << std::fixed << std::setprecision(3) << stat.getFrequency(word);

        std::ostringstream count;
        count << stat.getCount(word);

        std::vector<std::string> row = {word, count.str(), freq.str()};
        writer.write(row);
    }
    reader.close();
    writer.close();
    return 0;
}