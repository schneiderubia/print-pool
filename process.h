#pragma once

#include <csignal>
#include <thread>
#include <optional>
#include "pool.h"

class Process {
public:
    explicit Process(pid_t pid);

    void start(Pool &pool);

    static void simulate(const Process &process, Pool &pool);

private:
    pid_t pid;
    std::thread thread;

    static int randomNumber(int min, int max);

    static std::string randomFileName();
};