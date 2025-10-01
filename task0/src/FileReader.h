#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <string>

class FileReader {
private:
    std::string fileName;
    std::ifstream input;
    std:: string line;
public:
    explicit FileReader(const std::string& fileName);
    ~FileReader();
    bool isOpen();
    bool isEOF();
    const std::string& getLine();
};

#endif