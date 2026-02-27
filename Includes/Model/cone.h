#ifndef CONE_H
#define CONE_H

#include "solid.h"
#include<cstdio>
#include <istream>
#include <math.h>

class Cone : Solid
{
public:
    Cone();
    void ReadFromFile(FILE *ft) override;
    bool readFromStream(std::istream& in) override;
    void Display() override;
    [[nodiscard]] double getMin() const { return this->z[0] - h/2;}
    [[nodiscard]] double getMax() const { return this->z[0] + h/2;}
    [[nodiscard]] double getSection() const { return r0*r0*M_PI;}

private:
    double r0,r1,h,dr;
    int inte;
};

#endif // CONE_H
