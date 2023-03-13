#pragma once

#include <cstdlib>
#include <stdexcept>
#include "../../../2-infrastructure/RandomEngine.h"

class PerlinNoise {
public:
    PerlinNoise(const unsigned &cellSize = 24, const unsigned &octaves = 1, const double &persistence = 0.8,
                const unsigned &seed = 0)
            : cellSize(cellSize),
            octaves(octaves),
            persistence(persistence),
            seed(seed) {
        //To big octave may overflow double and not do much change in the final perlin noise
        if (octaves > 24) {
            throw std::invalid_argument("To big octave need less than 32");
        }

        if (this->seed != 0) {
            RandomEngine rand {seed};

            for (unsigned char &i: p) {
                i = static_cast<unsigned char>(rand.range(0,256));
            }
        }
    }

    [[nodiscard]] double perlin(const int &x) const;

    [[nodiscard]] double perlin(const int &x, const int &y) const;

    [[nodiscard]] double perlin(const int &x, const int &y, const int &z) const;

private:
    [[nodiscard]] double perlin1d(const double &x) const;

    [[nodiscard]] double perlin2d(const double &x, const double &y) const;

    [[nodiscard]] double perlin3d(const double &x, const double &y, const double &z) const;

    [[nodiscard]] unsigned char getP(const int &v) const {
        return p[v % 256];
    }

    static double lerp(const double &a, const double &b, const double &t) {
        return a + t * (b - a);
    }

    static int floor(const double &x) {
        auto const xi = static_cast<int>(x);
        return (x < static_cast<double>(xi)) ? xi - 1 : xi;
    }

    static double fade(const double &t) {
        return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
    }

    static double dot_grad(const int &hash, const double &xf) {
        // In 1D case, the gradient may be either 1 or -1
        // double the distance vector is the input offset (relative to the smallest bound)
        return (hash & 0x1) ? xf : -xf;
    }

    static double dot_grad(const int &hash, const double &xf, const double &yf) {
        // In 2D case, the gradient may be any of 8 direction vectors pointing to the
        // edges of a unit-square. double the distance vector is the input offset (relative to
        // the smallest bound
        double a[]{
                xf + yf, //0
                xf,  //1
                xf + -yf, // 2
                -yf, //3
                -xf + -yf,//4
                -xf, //5
                -xf + yf,//6
                yf     //7
        };

        int index = hash / 32; //[0,8[

        return a[index];
    }

    static inline auto dot_grad(const int &hash, const double &xf, const double &yf, const double &zf) -> double {
        // In 3D case, the gradient may be any of 12 direction vectors pointing to the edges
        // of a unit-cube (rounded to 16 with duplications). double the distance vector is the input
        // offset (relative to the smallest bound)
        switch (hash & 0xF) {
            case 0x0:
                return xf + yf;
            case 0x1:
                return -xf + yf;
            case 0x2:
                return xf - yf;
            case 0x3:
                return -xf - yf;
            case 0x4:
                return xf + zf;
            case 0x5:
                return -xf + zf;
            case 0x6:
                return xf - zf;
            case 0x7:
                return -xf - zf;
            case 0x8:
                return yf + zf;
            case 0x9:
                return -yf + zf;
            case 0xA:
                return yf - zf;
            case 0xB:
                return -yf - zf;
            case 0xC:
                return yf + xf;
            case 0xD:
                return -yf + zf;
            case 0xE:
                return yf - xf;
            case 0xF:
                return -yf - zf;
            default:
                return 0.0;
        }
    }


private:
    constexpr static unsigned int pSize = 256;
    unsigned char p[pSize] = {
            151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142,
            8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203,
            117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74,
            165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220,
            105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132,
            187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186,
            3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59,
            227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70,
            221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178,
            185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241,
            81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176,
            115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195,
            78, 66, 215, 61, 156, 180};
    const unsigned cellSize;
    const unsigned octaves;
    const double persistence;
    const unsigned int seed;
};

