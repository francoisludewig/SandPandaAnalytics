//
// Created by ludfr on 27/02/2026.
//

#pragma once
#include <string>
#include <vector>

class ContainerRepository;
class SphereRepository;

class ConvectionCalculator {
    double z_min{}, z_max{};
    double sectionSurface{};
    std::vector<double> verticalDisplacement;
    std::vector<double> radialPosition;
    double scale{};
public:
    explicit ConvectionCalculator(const ContainerRepository& ctr);
    void computeConvectionData(SphereRepository& sphr);
    void exportConvectionData(const std::string& directory);

};
