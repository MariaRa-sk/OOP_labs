#include "FileWriter.h"

FileWriter::FileWriter(const std::string &fileName)
    : fileName(fileName){
}

FileWriter::~FileWriter() {
    if (isOpen()) {
        output.close();
    }
}

void FileWriter::open() {
    output.open(fileName);
}

void FileWriter::close() {
    output.close();
}

bool FileWriter::isOpen() const {
    return output.is_open();
}

void FileWriter::write(const std::string& row) {
    output << row;
    output << "\n";
}