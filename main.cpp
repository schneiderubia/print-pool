#include <iostream>
#include <vector>
#include "pool.h"
#include "printer.h"
#include "process.h"
#include "log.h"

int main() {
    const unsigned int amountPrinter = 2;
    const unsigned int amountProcess = 4;
    unsigned int bufferSize;

    std::cout << "Insira o tamanho do buffer: ";
    std::cin >> bufferSize;

    Pool pool(bufferSize);

    Printer printer1(1);
    Printer printer2(2);

    pool.addPrinter(printer1);
    pool.addPrinter(printer2);

    Process p1(1);
    Process p2(2);
    Process p3(3);
    Process p4(4);

    p1.start(pool);
    p2.start(pool);
    p3.start(pool);
    p4.start(pool);

//    std::vector<Printer> printers;
//    for(int i = 1; i <= amountPrinter; i++) {
//        printers.emplace_back(i);
//    }
//
//    std::vector<Process> processes;
//    for(int i = 1; i <= amountProcess; i++) {
//        processes.emplace_back(i);
//        processes.back().start(pool);
//    }

    std::this_thread::sleep_for(std::chrono::seconds (60));
    return EXIT_SUCCESS;
}
