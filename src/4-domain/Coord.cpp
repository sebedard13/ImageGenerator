#include "Coord.h"

bool Coord::operator==(const Coord &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Coord::operator!=(const Coord &rhs) const {
    return !(rhs == *this);
}

Coord::Coord(int x, int y)
        : x(x),
          y(y) {
    checkRange();
}

void Coord::setSize(unsigned int width, unsigned int height) {
    Coord::width = width;
    Coord::height =height;
}

unsigned Coord::width = 256;
unsigned Coord::height = 256;

int Coord::getX() const {
    return x;
}

int Coord::getY() const {
    return y;
}

Coord Coord::operator+(const Coord &rhs) const {
    return {this->x+rhs.x, this->y+rhs.y};
}

void Coord::checkRange() {
    if(x < 0){
        x +=width;
    } else if (x >= width){
        x -=width;
    }

    if(y < 0){
        y +=height;
    } else if (y >= height){
        y -=height;
    }
}

Coord Coord::operator*(const int& rhs) const {
    return {this->x*rhs,this->y*rhs};
}

Coord Coord::operator-(const Coord &rhs) const {
    return {this->x-rhs.x,this->y-rhs.y};
}
