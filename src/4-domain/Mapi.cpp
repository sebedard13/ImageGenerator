#include "Mapi.h"

unsigned int Mapi::getWidth() const {
    return width;
}

unsigned int Mapi::getHeight() const {
    return height;
}

void Mapi::prepareRender()
{
    int min = array[0];
    int max = array[0];

    for (int i = 1; i < getSize(); ++i) {
        if (max < array[i]) {
            max = array[i];
        }

        if (min >array[i]) {
            min = array[i];
        }
    }

    colorInterpolate = ColorInterpolate<int>{ min, max, colors };
}

unsigned int Mapi::render(const unsigned int &i) const {
    return  colorInterpolate.uniformColor(array[i]);
}
unsigned int Mapi::getSize() const {
    return width*height;
}

void Mapi::setColors(std::vector<unsigned int> &&colors) {
   colors = colors;
}

Mapi::Mapi(const unsigned int width, const unsigned int height)
        : width(width),
          height(height) {
    array = new int[width*height]();

}

void Mapi::set(const unsigned& i, const int& value) {
    array[i] = value;
}

void Mapi::set(const Coord& c, const int& value) {
    set(c.getY() * width + c.getX(), value);
}

int Mapi::get(const Coord& c) const {
    return array[c.getY() * width + c.getX()];
}

Mapi::~Mapi() {
    delete[] array;
}
