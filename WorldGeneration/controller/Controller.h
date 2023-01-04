#pragma once
#include "../view/MapView.h"
#include "commands/Command.h"

class Controller
{
public:
	Controller() = delete;
	Controller(const Controller& other) = delete;
	Controller(Controller&& other) noexcept = delete;
	Controller& operator=(const Controller& other) = delete;
	Controller& operator=(Controller&& other) noexcept = delete;
	~Controller() = default;

	static void setUp(const std::shared_ptr<MapView>& mapView);
	static void execute(std::unique_ptr<Command> command);
private:
	explicit Controller(const std::shared_ptr<MapView>& mapView);

	std::shared_ptr<MapView> mapView;

	static Controller* instance;
};

