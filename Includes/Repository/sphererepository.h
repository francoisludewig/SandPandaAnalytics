#ifndef SPHEREREPOSITORY_H
#define SPHEREREPOSITORY_H

#include "../Model/sphere.h"
#include <vector>
#include <string>

class SphereRepository
{
public:
    SphereRepository();
    int getN() {return N;}
    void load(std::string directory);
private:
    std::vector<Sphere> spheres {};
    int N;
};

#endif // SPHEREREPOSITORY_H
