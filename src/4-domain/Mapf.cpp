#include "Mapf.h"

unsigned Mapf::render(const unsigned int &i) const {

    int value = ((array[i] - minf)/(maxf-minf))*max;

    return colorInterpolate.uniformColor(value);
}

Mapf::Mapf(unsigned int w, unsigned int h)
        : Map(w, h) {

}
