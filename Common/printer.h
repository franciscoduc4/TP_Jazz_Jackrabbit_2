#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <iostream>
#include <string>

#include <sys/types.h>

class Printer {
public:
    void printMessage(const std::string& message) {
        std::cout << message << std::endl;
    }

    void printErrorMessage(const std::string& message) {
        std::cerr << message << std::endl;
    }
};

#endif  // __PRINTER_H__
