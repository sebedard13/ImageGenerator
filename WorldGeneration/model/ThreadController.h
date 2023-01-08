#pragma once

#include <functional>
class ThreadController
{
public:
	static void setUp();
	static void runIteration(const unsigned min, const unsigned max, const std::function<void(unsigned i)>& func);
	static void setThreadNumber(const int nb);
private:
	ThreadController() {};
	ThreadController(const ThreadController& other) = delete;
	ThreadController(ThreadController&& other) noexcept = delete;
	ThreadController& operator=(const ThreadController& other) = delete;
	ThreadController& operator=(ThreadController&& other) noexcept = delete;

	static ThreadController* instance;
	void runIterationIns(const unsigned min, const unsigned max, const std::function<void(unsigned i)>& func);
	static void run(const unsigned min, const unsigned max, const std::function<void(unsigned i)>& func);

	int thread_nb = 8;
};

