#pragma once
#include "../Map.h"
#include "../../5-controller/MapView.h"
#include <memory>

class Algo
{
public:
	Algo() = default;
	Algo(const Algo& other) = delete;
	Algo(Algo&& other) noexcept = delete;
	Algo& operator=(const Algo& other) = delete;
	Algo& operator=(Algo&& other) noexcept = delete;

	virtual std::unique_ptr<Map> run() = 0;

	virtual ~Algo() = default;

	void setOutput(const std::shared_ptr<MapView>& mapView)
	{
		output = mapView;
	}
protected:
	std::shared_ptr<MapView> output{ nullptr };
};
