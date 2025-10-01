#include "FileWriter.h"

FileWriter::FileWriter(const std::string &fileName)
    : fileName(fileName){
    output.open(fileName);
}

FileWriter::~FileWriter() {
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


