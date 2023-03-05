#pragma once

#include <functional>
#include <cstdint>
#include "Coord.h"
#include "ColorInterpolate.h"

class Map {
public:
    Map()= default;

	Map(const Map& other) = delete;

	Map(Map&& other) = delete;

	Map& operator=(const Map& other) = delete;

	Map& operator=(Map&& other) = delete;

    [[nodiscard]] std::pair<int, int> toCoordinate(const int& i) const;

	virtual ~Map() = default;

    virtual unsigned getWidth() const=0;

    virtual unsigned getHeight() const=0;

    virtual unsigned getSize() const=0;

    virtual void prepareRender() =0;

	virtual unsigned render(const unsigned& i) const =0;


};

