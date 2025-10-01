#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <fstream>
#include <string>
#include <vector>

class FileWriter {
private:
    std::string fileName;
    std::ofstream output;
public:
    explicit FileWriter(const std::string& fileName);
    ~FileWriter();
    bool isOpen() const;
    void write(const std::vector<std::string>& row);
};

#endif