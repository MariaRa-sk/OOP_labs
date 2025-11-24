#include <iostream>

#include "FileReader.h"
#include "Parser.h"

int main() {
    Parser parser("input");
    parser.parseFile();
    return 0;
}