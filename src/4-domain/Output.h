#pragma once


#include <string>
#include "Map.h"

class Output {
public:
    Output() = default;

    Output(const Output& other) = delete;

    Output(Output&& other) noexcept = delete;

    Output& operator=(const Output& other) = delete;

    Output& operator=(Output&& other) noexcept = delete;

    ~Output() = default;

    virtual void setMessageId(const std::string& key) {};

    virtual void setPercent(unsigned int percent) {};

    virtual void loadMap(std::unique_ptr<Map>& map) {};

private:
};
