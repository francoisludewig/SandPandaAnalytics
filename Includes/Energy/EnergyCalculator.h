//
// Created by ludfr on 03/03/2026.
//

#pragma once
#include <string>
#include <vector>

class SphereRepository;
class ContainerRepository;

class EnergyCalculator {
    double z_min;
    std::vector<double> potentialEnergy{};
    std::vector<double> rotationalKineticEnergy{};
    std::vector<double> translationalKineticEnergy{};

public:
    EnergyCalculator(const ContainerRepository& ctr);
    void computeEnergy(SphereRepository& sphr);
    void exportEnergy(const std::string& directory);

};
