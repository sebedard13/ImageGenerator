#pragma once

#include "Algo.h"
#include <memory>
#include "../Map.h"


class DistanceFromCenter final : public Algo {
public:
    DistanceFromCenter(const DistanceFromCenter &other) = delete;

    DistanceFromCenter(DistanceFromCenter &&other) noexcept = delete;

    DistanceFromCenter &operator=(const DistanceFromCenter &other) = delete;

    DistanceFromCenter &operator=(DistanceFromCenter &&other) noexcept = delete;

    DistanceFromCenter() = default;

    std::unique_ptr<Map> run() override;

    ~DistanceFromCenter() override = default;
};

