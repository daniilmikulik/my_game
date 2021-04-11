#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H
#include <string>
#include <iostream>

class FileException{
private:
    std::string error;
public:
    FileException(std::string line){
        error = line;
        std::cout << line << std::endl;
    }
};

#endif // FILEEXCEPTION_H
