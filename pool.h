#pragma once

#include <queue>
#include <string>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include "printjob.h"
#include "printer.h"

class Printer;

class Pool {
public:
    explicit Pool(unsigned int bufferSize = 10);

    void receiveFile(pid_t process, std::string_view file, int priority = 3);

    void addPrinter(Printer &printer);

private:
    std::priority_queue<PrintJob> buffer;

    std::vector<std::pair<Printer, std::thread>> printers;

    unsigned int bufferSize;

    std::optional<PrintJob> sendFile();

    std::condition_variable cond_full;

    std::condition_variable cond_empty;

    std::mutex mutex;
};