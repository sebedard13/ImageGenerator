#pragma once

#include "Command.h"
#include "../../4-domain/algos/Algo.h"

class DoAlgo final : public Command {
public:
    explicit DoAlgo(std::unique_ptr<Algo> algo);

    DoAlgo(const DoAlgo &other) = delete;

    DoAlgo(DoAlgo &&other) noexcept = delete;

    DoAlgo &operator=(const DoAlgo &other) = delete;

    DoAlgo &operator=(DoAlgo &&other) noexcept = delete;

    void execute(const std::shared_ptr<MapView> &mapView) override;

    ~DoAlgo() override = default;

private:
    std::unique_ptr<Algo> algo;

};
