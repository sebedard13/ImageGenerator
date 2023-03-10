#pragma once
#include "Map.h"


class Mapf : public Map {
public:
    Mapf(unsigned int w, unsigned int h);

    Mapf(const Mapf &other) = delete;

    Mapf(Mapf &&other) noexcept = delete;

    Mapf &operator=(const Mapf &other) = delete;

    Mapf &operator=(Mapf &&other) noexcept = delete;

    ~Mapf() override = default;

    unsigned int getWidth() const override;

    unsigned int getHeight() const override;

    unsigned int getSize() const override;

    void prepareRender() override;

    virtual unsigned int render(const unsigned int &i) const override;

    std::vector<float> array{};

    void setColors(std::vector<unsigned int> &&colors);

private:
    const unsigned int width;
    const unsigned int height;
    ColorInterpolate<float> colorInterpolate{ 0,5 };
    std::vector<unsigned> colors{
            0xFF000000,
            0xFF0000FF,
            0xFF00FFFF,
            0xFF00FF00,
            0xFFFFFF00,
            0xFFFF0000,
            0xFFFFFFFF,
    };

};
