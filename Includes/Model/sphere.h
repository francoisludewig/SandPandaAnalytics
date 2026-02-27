#ifndef SPHERE_H
#define SPHERE_H

#include<vector>
#include<cstdio>
#include <istream>


class Sphere
{
public:
    Sphere();
    void ReadFromFile(FILE *ft);
    bool readFromStream(std::istream& in);
    [[nodiscard]] double getRadius() const {return r[0];}
    [[nodiscard]] double get_z_at(int i) const {return z[i];}

private:
    std::vector<double> x{},y{},z{};
    std::vector<double> nx{},ny{},nz{};
    std::vector<double> tx{},ty{},tz{};
    std::vector<double> sx{},sy{},sz{};
    std::vector<double> vx{},vy{},vz{};
    std::vector<double> wx{},wy{},wz{};
    std::vector<int> sp{};
    std::vector<double> r{};
    bool bd;
    //static StripeOnSphere sos;
    float VertexA[408][3];
    float VertexB[408][3];
};

#endif // SPHERE_H
