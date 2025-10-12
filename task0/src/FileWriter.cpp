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

void FileWriter::write(const std::vector<std::string>& row) {
    for (size_t i = 0; i < row.size(); ++i) {
        output << row[i];
        if (i != row.size() - 1) {
            output << ",";
        }
    }
    output << "\n";
}


