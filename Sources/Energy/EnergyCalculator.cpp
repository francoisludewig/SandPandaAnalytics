//
// Created by ludfr on 03/03/2026.
//

#include "../../Includes/Energy/EnergyCalculator.h"

#include "../../Includes/Repository/sphererepository.h"
#include "../../Includes/Repository/containerrepository.h"

#include <cmath>
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <iomanip>

EnergyCalculator::EnergyCalculator(const ContainerRepository& ctr) {
    if (ctr.hasCones() > 0) {
        const auto cone = ctr.getCone();
        z_min = cone.getMin();
    } else {
        //TODO Analyse Box case
        z_min = 0;
    }
}


void EnergyCalculator::computeEnergy(SphereRepository& sphr) {
    double density = 2500;
    double m = 0, I = 0;
    for (int j = 0 ; j < sphr.getN() ; j++) {
        potentialEnergy.push_back(0);
        rotationalKineticEnergy.push_back(0);
        translationalKineticEnergy.push_back(0);
    }
    // Loop over spheres in the packing
    for (const auto& sphere : sphr) {
        // Loop over the step
        for (int j = 0 ; j < sphr.getN()  ; j++) {
            m = 4.0/3.0*M_PI* std::pow(sphere.getRadius(),3)*density;
            I = 2.0/5.0*m*std::pow(sphere.getRadius(),2);
            potentialEnergy[j] += (sphere.get_z_at(j)-z_min)*9.81*m;
            translationalKineticEnergy[j] += sphere.get_translational_squared_speed_at(j)*0.5*m;
            rotationalKineticEnergy[j] += sphere.get_rotational_squared_speed_at(j)*0.5*I;
        }
    }
}

void EnergyCalculator::exportEnergy(const std::string& directory) {
    namespace fs = std::filesystem;

    // Dossier cible : <directory>/PackingFraction
    const fs::path baseDir(directory);
    const fs::path outDir = baseDir / "Energy";

    // Création (idempotente)
    std::error_code ec;
    fs::create_directories(outDir, ec);
    if (ec)
        throw std::runtime_error("Cannot create directory: " + outDir.string() + " (" + ec.message() + ")");

    const fs::path filePath = outDir / "energy.txt";
    std::ofstream ofs(filePath);
    if (!ofs)
        throw std::runtime_error("Cannot open file for writing: " + filePath.string());

    // Format numérique précis (utile si post-traitement scientifique)
    ofs << std::setprecision(17);

    for (std::size_t i = 0; i < potentialEnergy.size(); ++i)
    {
        ofs << i << '\t' << potentialEnergy[i] << '\t' << translationalKineticEnergy[i] << '\t' << rotationalKineticEnergy[i] << '\n';
    }
}
