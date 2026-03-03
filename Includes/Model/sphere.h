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
    [[nodiscard]] double get_translational_squared_speed_at(int i) const {return  vx[i]*vx[i]+vy[i]*vy[i]+vz[i]*vz[i];}
    [[nodiscard]] double get_rotational_squared_speed_at(int i) const {return  wx[i]*wx[i]+wy[i]*wy[i]+wz[i]*wz[i];}

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
