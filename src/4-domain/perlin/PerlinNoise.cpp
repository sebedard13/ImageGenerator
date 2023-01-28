#include "PerlinNoise.h"

double PerlinNoise::perlin(const int &x) const {
    double total = 0;
    double frequency = 1;
    double amplitude = 1;
    double maxValue = 0;  // Used for normalizing result to 0.0 - 1.0
    for (unsigned i = 0; i < octaves; i++) {
        total += perlin1d(x * frequency / cellSize) * amplitude;

        maxValue += amplitude;

        amplitude *= persistence;
        frequency *= 2;
    }

    return total / maxValue;
}

double PerlinNoise::perlin(const int &x, const int &y) const {
    double total = 0;
    double frequency = 1;
    double amplitude = 1;
    double maxValue = 0;  // Used for normalizing result to 0.0 - 1.0
    for (unsigned i = 0; i < octaves; i++) {
        total += perlin2d(x * frequency / cellSize, y * frequency / cellSize) * amplitude;

        maxValue += amplitude;

        amplitude *= persistence;
        frequency *= 2;
    }
    return total / maxValue;
}

double PerlinNoise::perlin(const int &x, const int &y, const int &z) const {
    double total = 0;
    double frequency = 1;
    double amplitude = 1;
    double maxValue = 0;  // Used for normalizing result to 0.0 - 1.0
    for (unsigned i = 0; i < octaves; i++) {
        total += perlin3d(x * frequency / cellSize, y * frequency / cellSize, z * frequency / cellSize) * amplitude;

        maxValue += amplitude;

        amplitude *= persistence;
        frequency *= 2;
    }

    return total / maxValue;
}

double PerlinNoise::perlin1d(const double &x) const {
    // Left coordinate of the unit-line that contains the input
    int const xi0 = floor(x);

    // Input location in the unit-line
    double const xf0 = x - static_cast<double>(xi0);
    double const xf1 = xf0 - 1.0;

    // Wrap to range 0-255
    int const xi = xi0 & 0xFF;

    // Apply the fade function to the location
    double const u = fade(xf0);

    // Generate hash values for each point of the unit-line
    int const h0 = getP(xi + 0);
    int const h1 = getP(xi + 1);

    // Linearly interpolate between dot products of each gradient with its distance to the input location
    return lerp(dot_grad(h0, xf0), dot_grad(h1, xf1), u);
}

double PerlinNoise::perlin2d(const double &x, const double &y) const {
    // double top-left coordinates of the unit-square
    int const xi0 = floor(x);
    int const yi0 = floor(y);

    // Input location in the unit-square
    double const xf0 = x - static_cast<double>(xi0);
    double const yf0 = y - static_cast<double>(yi0);
    double const xf1 = xf0 - 1.0;
    double const yf1 = yf0 - 1.0;

    // Wrap to range 0-255
    int const xi = xi0 & 0xFF;
    int const yi = yi0 & 0xFF;

    // Apply the fade function to the location
    double const u = fade(xf0);
    double const v = fade(yf0);

    // Generate hash values for each point of the unit-square
    int const h00 = getP(getP(xi + 0) + yi + 0);
    int const h01 = getP(getP(xi + 0) + yi + 1);
    int const h10 = getP(getP(xi + 1) + yi + 0);
    int const h11 = getP(getP(xi + 1) + yi + 1);

    // Linearly interpolate between dot products of each gradient with its distance to the input location
    double const x1 = lerp(dot_grad(h00, xf0, yf0), dot_grad(h10, xf1, yf0), u);
    double const x2 = lerp(dot_grad(h01, xf0, yf1), dot_grad(h11, xf1, yf1), u);
    double const ret = lerp(x1, x2, v);
    return ret;
}

double PerlinNoise::perlin3d(const double &x, const double &y, const double &z) const {
    // Top-left coordinates of the unit-cube
    int const xi0 = floor(x);
    int const yi0 = floor(y);
    int const zi0 = floor(z);

    // Input location in the unit-cube
    double const xf0 = x - static_cast<double>(xi0);
    double const yf0 = y - static_cast<double>(yi0);
    double const zf0 = z - static_cast<double>(zi0);
    double const xf1 = xf0 - 1.0;
    double const yf1 = yf0 - 1.0;
    double const zf1 = zf0 - 1.0;

    // Wrap to range 0-255
    int const xi = xi0 & 0xFF;
    int const yi = yi0 & 0xFF;
    int const zi = zi0 & 0xFF;

    // Apply the fade function to the location
    double const u = fade(xf0);
    double const v = fade(yf0);
    double const w = fade(zf0);

    // Generate hash values for each point of the unit-cube
    int const h000 = getP(getP(getP(xi + 0) + yi + 0) + zi + 0);
    int const h001 = getP(getP(getP(xi + 0) + yi + 0) + zi + 1);
    int const h010 = getP(getP(getP(xi + 0) + yi + 1) + zi + 0);
    int const h011 = getP(getP(getP(xi + 0) + yi + 1) + zi + 1);
    int const h100 = getP(getP(getP(xi + 1) + yi + 0) + zi + 0);
    int const h101 = getP(getP(getP(xi + 1) + yi + 0) + zi + 1);
    int const h110 = getP(getP(getP(xi + 1) + yi + 1) + zi + 0);
    int const h111 = getP(getP(getP(xi + 1) + yi + 1) + zi + 1);

    // Linearly interpolate between dot products of each gradient with its distance to the input location
    double const x11 = lerp(dot_grad(h000, xf0, yf0, zf0), dot_grad(h100, xf1, yf0, zf0), u);
    double const x12 = lerp(dot_grad(h010, xf0, yf1, zf0), dot_grad(h110, xf1, yf1, zf0), u);
    double const x21 = lerp(dot_grad(h001, xf0, yf0, zf1), dot_grad(h101, xf1, yf0, zf1), u);
    double const x22 = lerp(dot_grad(h011, xf0, yf1, zf1), dot_grad(h111, xf1, yf1, zf1), u);

    double const y1 = lerp(x11, x12, v);
    double const y2 = lerp(x21, x22, v);

    return lerp(y1, y2, w);
}
