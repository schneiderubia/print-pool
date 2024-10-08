#pragma once

#include <vector>
#include "pool.h"

class Printer {
public:
    explicit Printer(unsigned int id, unsigned int latency = 100);

    Printer(const Printer &other) = default;

    virtual ~Printer();

    void printFile(PrintJob& pj);

    void printReport();

    [[nodiscard]] unsigned int getId() const;

private:
    unsigned int id;
    unsigned int latency;
    std::vector<PrintJob> report;
};