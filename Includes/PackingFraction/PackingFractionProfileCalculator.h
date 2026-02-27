//
// Created by ludfr on 27/02/2026.
//

#pragma once
#include <string>
#include <vector>

class ContainerRepository;
class SphereRepository;

class PackingFractionProfileCalculator {
    double z_min{}, z_max{};
    double sectionSurface{};
    std::vector<std::vector<double>> profiles;
    std::vector<double> packingFractions;
    double scale;
public:
    explicit PackingFractionProfileCalculator(ContainerRepository& ctr);
    void computePackingFractionProfile(SphereRepository& sphr);
    void computePackingFraction();
    void exportProfiles(const std::string& directory);
    void exportPackingFractions(const std::string& directory);
};
