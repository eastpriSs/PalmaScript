#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "CharDriver.hpp"
#include "LineDriver.hpp"
#include "Compiler.hpp"

inline bool isFileExist(char * filename) 
{
    if (FILE* file = fopen(filename, "r")) {
        fclose(file);
        return true;
    }
    else {
        return false;
    }
}


void printInfo() {
    
}

int main(int argc, char * argv[])
{
    if (argc <= 1) {
        printInfo();
        return 1;
    }

    if (!isFileExist(argv[1])) {
        printf("File %s is not exist.", argv[1]);
    }

    std::string filename = std::string(argv[1]);
    CharDriver::CharStream chstream;
    CharDriver::error_code errc = CharDriver::CharStreamStuff::fillCharStream(filename, chstream);
    
    if (errc == CharDriver::error_code::file_not_open) {
        printf("File %s is not open.", argv[1]);
        return 1;
    }

    lineDriver::LineDriver::instance().setPath(filename);
    Compiler cmplr;
    cmplr.Compile(chstream);
}

