#pragma once

#include <iostream>
#include <format>
#include <chrono>
#include <mutex>

class Log {
public:
    static Log& getInstance() {
        static Log logger;
        return logger;
    }

    void print(const std::string &message) {
        std::lock_guard lock(mutex);
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        output << std::put_time(std::localtime(&time), "%H:%M:%S")
               << '.' << std::setw(3) << std::setfill('0') << ms.count() << " | "
               << message << std::endl;
    }

private:
    explicit Log(std::ostream &output = std::cout) : output(output) {}

    std::ostream &output;
    std::mutex mutex;
};