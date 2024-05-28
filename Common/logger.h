#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <chrono>
#include <ctime>
#include <fstream>
#include <string>

class Logger {
private:
    std::ofstream fileStream;

    std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        char buf[100];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S%z", std::localtime(&now_c));
        return buf;
    }

public:
    explicit Logger(const std::string& filePath) { fileStream.open(filePath, std::ios_base::app); }

    ~Logger() {
        if (fileStream.is_open()) {
            fileStream.close();
        }
    }

    template <typename... Args>
    void debug(const std::string& func, const int& line, const std::string& format, Args... args) {
        fileStream << getCurrentTime() << " | DEBUG | Function: " << func << " | Line: " << line
                   << " | " << std::format(format, args...) << std::endl;
    }

    template <typename... Args>
    void error(const std::string& func, int line, const std::string& format, Args... args) {
        fileStream << getCurrentTime() << " | ERROR | Function: " << func << " | Line: " << line
                   << " | " << std::format(format, args...) << std::endl;
    }

    template <typename... Args>
    void info(const std::string& func, int line, const std::string& format, Args... args) {
        fileStream << getCurrentTime() << " | INFO | Function: " << func << " | Line: " << line
                   << " | " << std::format(format, args...) << std::endl;
    }

};

#endif  // __LOGGER_H__
