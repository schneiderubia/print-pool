#pragma once

#include <string>
#include <chrono>
#include <csignal>
#include <iomanip>
#include <iostream>

class PrintJob {
public:

    PrintJob(pid_t process, std::string_view file, int priority) :
            process(process), file(file), priority(priority),
            request_time(std::chrono::system_clock::now()) {}

    PrintJob(const PrintJob &orig) = default;

    bool operator<(const PrintJob &other) const noexcept {
        if(priority == other.priority) {
            return request_time < other.request_time;
        }
        return priority < other.priority;
    }

    [[nodiscard]] pid_t getProcess() const {
        return process;
    }

    [[nodiscard]] const std::string &getFile() const {
        return file;
    }

    [[nodiscard]] const std::chrono::system_clock::time_point &getRequestTime() const {
        return request_time;
    }

    [[nodiscard]] const std::chrono::system_clock::time_point &getPrintTime() const {
        return print_time;
    }

    void setPrintTime(const std::chrono::system_clock::time_point &printTime) {
        print_time = printTime;
    }

    [[nodiscard]] int getPriority() const {
        return priority;
    }

    [[nodiscard]] std::string getRequestTimeStr() const {
        return timeToString(request_time);
    }

    [[nodiscard]] std::string getPrintTimeStr() const {
        return timeToString(print_time);
    }

    [[nodiscard]] static std::string timeToString(std::chrono::system_clock::time_point tp) {
        auto time_t = std::chrono::system_clock::to_time_t(tp);
        auto duration_since_epoch = tp.time_since_epoch();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration_since_epoch) % 1000;

        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%H:%M:%S")
           << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();
        return ss.str();
    }

private:
    pid_t process;
    std::string file;
    std::chrono::system_clock::time_point request_time;
    std::chrono::system_clock::time_point print_time;
    int priority;
};