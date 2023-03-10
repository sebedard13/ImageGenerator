#pragma once


#include "Map.h"

class Mapi: public Map {
public:
    Mapi() = delete;

    Mapi(const Mapi &other) = delete;

    Mapi(Mapi &&other) noexcept = delete;

    Mapi &operator=(const Mapi &other) = delete;

    Mapi &operator=(Mapi &&other) noexcept = delete;

    ~Mapi() override;

    unsigned int getWidth() const override;

    unsigned int getHeight() const override;

    unsigned int getSize() const override;

    void prepareRender() override;

    unsigned int render(const unsigned int &i) const override;
    std::vector<unsigned> colors{
            0xFF000000,
            0xFF0000FF,
            0xFF00FFFF,
            0xFF00FF00,
            0xFFFFFF00,
            0xFFFF0000,
            0xFFFFFFFF,
    };

    void setColors(std::vector<unsigned int>&& colors);

    Mapi(const unsigned int width, const unsigned int height);

    int* array;
    void set(const unsigned int &i, const int &value);

    void set(const Coord &c, const int &value);

    int get(const Coord &c) const;

private:
    const unsigned int width;
    const unsigned int height;
    ColorInterpolate<int> colorInterpolate{ 0,5 };
};
