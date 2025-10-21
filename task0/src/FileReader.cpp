#include "FileReader.h"

#include <fstream>
#include <string>

FileReader::FileReader(const std::string &fileName)
        :fileName(fileName) {
}

FileReader::~FileReader() {
    if (isOpen()) {
        input.close();
    }
}

void FileReader::open() {
    input.open(fileName);
}

void FileReader::close() {
    input.close();
}

bool FileReader::isOpen() {
    return input.is_open();
}

bool FileReader::isEOF() {
        return input.peek() == std::char_traits<char>::eof();
}

const std::string& FileReader::getLine() {
    std::getline(input, line);
    return line;
}




