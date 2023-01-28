#pragma once
#include <functional>

void setTimeout(int milliseconds, const std::function<void()>& func);