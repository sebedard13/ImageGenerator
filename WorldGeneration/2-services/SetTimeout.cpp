#include "SetTimeout.h"
#include <thread>

void setTimeout(int milliseconds, const std::function<void()> &func) {
    std::thread thread_object([=]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
        func();
    });
    thread_object.detach();
}
