#include "pool.h"
#include "log.h"
#include <string>

Pool::Pool(const unsigned int bufferSize) : buffer(), bufferSize(bufferSize) {}

void Pool::receiveFile(pid_t process, std::string_view file, int priority) {
    std::unique_lock<std::mutex> lock(mutex);
    cond_full.wait(lock, [this] { return buffer.size() < bufferSize; });
    Log::getInstance().print(
            std::format("Recebendo arquivo {} do processso {} com prioridade {}", file.data(), process, priority));
    const PrintJob pj(process, file, priority);
    buffer.push(pj);
    cond_empty.notify_one();
}

std::optional<PrintJob> Pool::sendFile() {
    std::unique_lock<std::mutex> lock(mutex);
    cond_empty.wait(lock, [this] { return !buffer.empty(); });
        auto pj = buffer.top();
        buffer.pop();
        cond_empty.notify_one();
        return pj;
}

void Pool::addPrinter(Printer &printer) {
    std::thread t([this, &printer] {
        while (true) {
            auto pj = sendFile();
            if (pj.has_value()) {
                printer.printFile(pj.value());
            }
        }
    });
    t.detach();
}




