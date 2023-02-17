#pragma once


class Coord {
public:

    Coord(const Coord &other) = default;

    Coord(Coord &&other) noexcept = default;

    Coord &operator=(const Coord &other) = default;

    Coord &operator=(Coord &&other) noexcept = default;

    ~Coord() = default;

    Coord() = default;
    Coord(int x, int y);

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;

    static void setSize(unsigned width, unsigned height);

    bool operator==(const Coord &rhs) const;

    bool operator!=(const Coord &rhs) const;

    Coord operator +(const Coord &rhs) const;

    Coord operator *(const int &rhs) const;

    Coord operator -(const Coord &rhs) const;



private:
    int x {0};
    int y {0};

    static unsigned width;
    static unsigned height;

    void checkRange();
};
