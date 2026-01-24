#ifndef SOLID_H
#define SOLID_H

#include<cstdio>
#include<vector>
#include "velocity.h"
#include <istream>

class Solid
{
public:
    Solid();
    virtual void ReadFromFile(FILE *ft);
    virtual bool readFromStream(std::istream& in);
    virtual void Display();
protected:
    std::vector<double> x{},y{},z{};
    std::vector<double> nx{},ny{},nz{};
    std::vector<double> tx{},ty{},tz{};
    std::vector<double> sx{},sy{},sz{};
    std::vector<Velocity> vx{},vy{},vz{};
    std::vector<Velocity> wx{},wy{},wz{};
    double beta;
    double orx,ory,orz;
    double Vx,Vy,Vz,Wx,Wy,Wz;
    int Ngb;
    int N,Nold;
};

#endif // SOLID_H
