#pragma once

#include "Command.h"

class SaveImage :
        public Command {
public:

    SaveImage(const std::string &p)
            : path(p) {

    }

    SaveImage(const SaveImage &other) = delete;

    SaveImage(SaveImage &&other) noexcept = delete;

    SaveImage &operator=(const SaveImage &other) = delete;

    SaveImage &operator=(SaveImage &&other) noexcept = delete;

    void execute(const std::shared_ptr<MapView> &mapView) override;

    ~SaveImage() override = default;

private:
    const std::string path;
};

