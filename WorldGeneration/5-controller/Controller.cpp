#include "Controller.h"

Controller* Controller::instance = nullptr;

Controller::Controller(const std::shared_ptr<MapView>& mapView) : mapView(mapView) {

}

void Controller::setUp(const std::shared_ptr<MapView>& mapView)
{
	Controller::instance = new Controller(mapView);
}

void Controller::execute(std::unique_ptr<Command> command)
{
	command->execute(instance->mapView);
}
