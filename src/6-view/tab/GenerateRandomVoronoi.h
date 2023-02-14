#pragma once


#include "TabRandomVoronoi.h"
#include "TabAlgo.h"

class GenerateRandomVoronoi : public TabAlgo {
public:
    GenerateRandomVoronoi(TabRandomVoronoi* tabRandomVoronoi);

    GenerateRandomVoronoi(const GenerateRandomVoronoi &other) = delete;

    GenerateRandomVoronoi(GenerateRandomVoronoi &&other) noexcept = delete;

    GenerateRandomVoronoi &operator=(const GenerateRandomVoronoi &other) = delete;

    GenerateRandomVoronoi &operator=(GenerateRandomVoronoi &&other) noexcept = delete;

    ~GenerateRandomVoronoi() = default;

    void handleGenerate() override;

private:
    TabRandomVoronoi* tabRandomVoronoi;
};
