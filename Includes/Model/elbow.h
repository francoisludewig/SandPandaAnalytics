#ifndef ELBOW_H
#define ELBOW_H

#include<cstdio>
#include<vector>
#include "velocity.h"

class Elbow
{
public:
    Elbow();
    void ReadFromFile(FILE *ft);
    bool readFromStream(std::istream& in);

private:
    std::vector<double> xi{},yi{},zi{};
    std::vector<double> xf{},yf{},zf{};
    std::vector<double> xr{},yr{},zr{};
    std::vector<double> nx{},ny{},nz{};
    std::vector<double> tx{},ty{},tz{};
    std::vector<double> sx{},sy{},sz{};
    std::vector<Velocity> vx{},vy{},vz{};
    std::vector<Velocity> wx{},wy{},wz{};
    double cx,cy,cz,radius,Rc,alpha;
    double orx, ory, orz;
    int N;
};

#endif // ELBOW_H
