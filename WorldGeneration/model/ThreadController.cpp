#include "ThreadController.h"
#include <thread>

ThreadController* ThreadController::instance = nullptr;

void ThreadController::setUp()
{
	instance = new ThreadController();
}

void ThreadController::runIteration(const unsigned min, const unsigned max, const std::function<void(unsigned i)>& func)
{
	instance->runIterationIns(min, max, func);
}

void ThreadController::setThreadNumber(const int nb)
{
	instance->thread_nb = nb;
}

void ThreadController::runIterationIns(const unsigned min, const unsigned max, const std::function<void(unsigned i)>& func)
{
	std::vector<std::thread> threads(thread_nb);

	const unsigned range = (max - min) / threads.size(); // may floor and miss some
	for (unsigned i = 0; i < threads.size() - 1; ++i)
	{
		threads[i] = std::thread(&ThreadController::run, i * range + min, (i + 1) * range + min, func);
	}

	//last thread do to max to not miss any;
	threads[threads.size() - 1] = std::thread(&ThreadController::run, static_cast<unsigned>((threads.size() - 1)) * range + min, max, func);

	for (auto& thread : threads)
	{
		thread.join();
	}
}

void ThreadController::run(const unsigned min, const unsigned max, const std::function<void(unsigned i)>& func)
{
	for (unsigned i = min; i < max; ++i)
	{
		func(i);
	}
}
