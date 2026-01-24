#ifndef VELOCITY_H
#define VELOCITY_H

#include<cstdio>
#include <istream>

class Velocity
{
public:
    Velocity();
    void ReadFromFile(FILE *ft);
    bool readFromStream(std::istream& in);

    double A0,A1,w,p;
};

#endif // VELOCITY_H
