#include "Mapf.h"

unsigned Mapf::render(const unsigned int& i) const {

	return colorInterpolate.uniformColor(std::floor(array[i]));
}

Mapf::Mapf(unsigned int w, unsigned int h) : width(w), height(h) {

}

void Mapf::setColors(std::vector<unsigned int>&& colors) {
	this->colors = colors;
}

unsigned int Mapf::getWidth() const {
	return width;
}

unsigned int Mapf::getHeight() const {
	return height;
}

unsigned int Mapf::getSize() const {
	return width * height;
}

void Mapf::prepareRender() {
	float min = array[0];
	float max = array[0];

	for (int i = 1; i < getSize(); ++i) {
		if (max < array[i]) {
			max = array[i];
		}

		if (min > array[i]) {
			min = array[i];
		}
	}

	colorInterpolate = ColorInterpolate<float>{ std::floor(min),std::floor(max),colors };
	int a = 2;
}
