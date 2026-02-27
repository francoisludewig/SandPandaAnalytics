 #pragma once

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
    [[nodiscard]] int getN() const {return N;}
    void load(std::string directory);
    [[nodiscard]] bool hasCones() const { return !cones.empty();}
    [[nodiscard]] Cone getCone() const {return cones[0];};

private:
    std::vector<Plan> plans {};
    std::vector<Disk> disks {};
    std::vector<Cone> cones {};
    std::vector<Elbow> elbows {};
    int N{0};
};
