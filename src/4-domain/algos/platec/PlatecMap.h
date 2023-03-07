#pragma once


#include <array>
#include "../../Map.h"

class PlatecMap : public Map{
public:
    PlatecMap(const PlatecMap &other) = delete;

    PlatecMap(PlatecMap &&other) noexcept = delete;

    PlatecMap &operator=(const PlatecMap &other) = delete;

    PlatecMap &operator=(PlatecMap &&other) noexcept = delete;

    ~PlatecMap() = default;

    unsigned int getWidth() const override;

    unsigned int getHeight() const override;

    unsigned int getSize() const override;

    void prepareRender() override;

    unsigned int render(const unsigned int &i) const override;

    PlatecMap(const unsigned int width, const unsigned int height);


    std::vector<float> array{};

    std::vector<ColorInterpolate<float>> colorInterpolates{};

    // Satellite color map:
    // 0.0:   0,   0,  64
    // 0.5:   0,   0, 255
    // 1.0:   0, 255, 255
    //
    // 1.0:   0, 128,   0
    // 2.0:   0, 255,   0
    // 2.5: 255, 255,   0
    // 3.0: 255, 128,   0
    // 4.0  128,  64,   0
    // 6.0:  96,  96,  96
    // 9.0: 255, 255, 255 // Snow capped mountains
    std::array<std::pair<float, unsigned>, 11> colorsMap{
            std::pair<float, unsigned> {0.0f, 0xff000040},
            std::pair<float, unsigned> {0.5f, 0xff0000ff},
            std::pair<float, unsigned> {1.0f, 0xff00ffff},

            std::pair<float, unsigned> {1.001f, 0xff008000},
            std::pair<float, unsigned> {3.0f, 0xff00ff00},
            std::pair<float, unsigned> {3.5f, 0xffffff00},
            std::pair<float, unsigned> {4.0f, 0xffff8000},
            std::pair<float, unsigned> {5.0f, 0xff804000},
            std::pair<float, unsigned> {7.0f, 0xff606060},
            std::pair<float, unsigned> {10.0f, 0xffffffff},
    };
private:
    const unsigned int width;
    const unsigned int height;
};
