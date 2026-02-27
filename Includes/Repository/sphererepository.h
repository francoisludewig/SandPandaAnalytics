#pragma once
#include "../Model/sphere.h"
#include <vector>
#include <string>

class SphereRepository
{
public:

    using iterator = std::vector<Sphere>::iterator;
    using const_iterator = std::vector<Sphere>::const_iterator;

    SphereRepository();
    [[nodiscard]] int getN() const {return N;}
    void load(const std::string& directory);
    [[nodiscard]] double minimal_radius() const;

    iterator begin() { return spheres.begin(); }
    iterator end()   { return spheres.end(); }

    [[nodiscard]] const_iterator begin() const { return spheres.begin(); }
    [[nodiscard]] const_iterator end()   const { return spheres.end(); }

    [[nodiscard]] const_iterator cbegin() const { return spheres.cbegin(); }
    [[nodiscard]] const_iterator cend()   const { return spheres.cend(); }
private:
    std::vector<Sphere> spheres {};
    int N{};
};
