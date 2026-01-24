#ifndef CONE_H
#define CONE_H

#include "solid.h"
#include<cstdio>
#include <istream>

class Cone : Solid
{
public:
    Cone();
    void ReadFromFile(FILE *ft) override;
    bool readFromStream(std::istream& in) override;
    void Display();
private:
    double r0,r1,h,dr;
    int inte;
};

#endif // CONE_H
