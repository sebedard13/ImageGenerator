#pragma once

#include <atomic>
#include <functional>
#include "../5-controller/MapView.h"

struct Counters {
    unsigned int currentOperation = 0;
    bool done = false;
};

class ThreadController {
public:
    ThreadController();

    ThreadController(MapView *output);

    ThreadController(const ThreadController &other) = delete;

    ThreadController(ThreadController &&other) noexcept = delete;

    ThreadController &operator=(const ThreadController &other) = delete;

    ThreadController &operator=(ThreadController &&other) noexcept = delete;

    ~ThreadController();

    static void setThreadNumber(unsigned nb);

    void runIteration(const unsigned min, const unsigned max, const std::function<void(unsigned i)> &func);

    void runIterationOutput(const unsigned min, const unsigned max, const std::function<void(unsigned i)> &func);

    [[nodiscard]] bool isDone() const;

    [[nodiscard]] unsigned getDoneOperations() const;

private:
    std::atomic<Counters> *counters = nullptr;
    MapView *output{nullptr};
    static unsigned THREADS;

    void run(std::atomic<Counters> *counter, const unsigned min, const unsigned max,
             const std::function<void(unsigned i)> &func);

    const int threadCount = 8;
};


