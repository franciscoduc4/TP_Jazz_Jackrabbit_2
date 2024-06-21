#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <iostream>
#include <string>

#include <sys/types.h>
#include <fmt/core.h>
#include <fmt/color.h>

class Printer {
public:
    static void printMessage(const std::string& message) {
        std::cout << message << std::endl;
    }

    static void printErrorMessage(const std::string& message) {
        std::cerr << message << std::endl;
    }

    static void printDebugMessage(const std::string& message) {
        fmt::print(fg(fmt::color::yellow), "{}\n", message);
    }

    static void printSuccessMessage(const std::string& message) {
        fmt::print(fg(fmt::color::green), "{}\n", message);
    }

    static void printWarningMessage(const std::string& message) {
        fmt::print(fg(fmt::color::orange), "{}\n", message);
    }

    static void printErrorMessage(const std::string& message, const std::string& error) {
        fmt::print(fg(fmt::color::red), "{}: {}\n", message, error);
    }

    static void printDebugHighlightedMessage(const std::string& message) {
        fmt::print(fmt::emphasis::bold | fg(fmt::color::black) | bg(fmt::color::yellow), "{}\n", message);
    }

    static void printSuccessHighlightedMessage(const std::string& message) {
        fmt::print(fmt::emphasis::bold | fg(fmt::color::black) | bg(fmt::color::green), "{}\n", message);
    }

    static void printWarningHighlightedMessage(const std::string& message) {
        fmt::print(fmt::emphasis::bold | fg(fmt::color::black) | bg(fmt::color::orange), "{}\n", message);
    }

    static void printErrorHighlightedMessage(const std::string& message) {
        fmt::print(fmt::emphasis::bold | fg(fmt::color::white) | bg(fmt::color::red), "{}\n", message);
    }
};

#endif  // __PRINTER_H__
