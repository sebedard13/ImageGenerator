#pragma once

#include "../MapView.h"

class Command
{
public:
	Command() =default;
	Command(const Command& other) = delete;
	Command(Command&& other) noexcept = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other) noexcept = delete;

	virtual void execute(const std::shared_ptr<MapView>& mapView) = 0;

	virtual ~Command() = default;
};
