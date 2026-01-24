#ifndef CONTAINERREPOSITORY_H
#define CONTAINERREPOSITORY_H

#include <string>
#include<vector>
#include "../Model/plan.h"
#include "../Model/disk.h"
#include "../Model/cone.h"
#include "../Model/elbow.h"

class ContainerRepository
{
public:
    ContainerRepository();
    int getN() {return N;}
    void load(std::string directory);
private:
    std::vector<Plan> plans {};
    std::vector<Disk> disks {};
    std::vector<Cone> cones {};
    std::vector<Elbow> elbows {};
    int N;
};

#endif // CONTAINERREPOSITORY_H
