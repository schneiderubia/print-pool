#include <thread>
#include <iomanip>
#include "printer.h"
#include "log.h"

Printer::Printer(unsigned int id, unsigned int latency) : id(id), latency(latency), report() {

}

void Printer::printReport() {
    Log::getInstance().print(std::format(">>> Relatório da impressora {} <<<", id));
    for(auto &pj : report){
        Log::getInstance().print(std::format("Hora da requisição: {}, Hora da impressão: {}, Processo: {}, Arquivo: {}", pj.getRequestTimeStr(),pj.getPrintTimeStr(),pj.getProcess(), pj.getFile()));
    }
}

void Printer::printFile(PrintJob &pj) {
    Log::getInstance().print(std::format("Impressora {} imprimindo arquivo {} do processo {}", id, pj.getFile(), pj.getProcess()));
    pj.setPrintTime(std::chrono::system_clock::now());
    report.push_back(pj);
    std::this_thread::sleep_for(std::chrono::milliseconds (latency));
}

unsigned int Printer::getId() const {
    return id;
}

Printer::~Printer() {
    printReport();
}
