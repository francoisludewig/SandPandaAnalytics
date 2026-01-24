#ifndef DISK_H
#define DISK_H

#include "solid.h"
#include<cstdio>

class Disk : Solid
{
public:
    Disk();
    void ReadFromFile(FILE *ft) override;
    bool readFromStream(std::istream& in) override;
    void Display();
private:
    double r;
    int periodic;
};

#endif // DISK_H
