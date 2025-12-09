#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <fstream>
#include <string>

class FileWriter {
private:
    std::string fileName;
    std::ofstream output;
public:
    explicit FileWriter(const std::string& fileName);
    ~FileWriter();
    void open();
    void close();
    bool isOpen() const;
    void write(const std::string& row);
};

#endif