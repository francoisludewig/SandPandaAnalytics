//
// Created by ludfr on 01/06/2026.
//


#include "../../Includes/Convection/ConvectionCalculator.h"

#include <iomanip>
#include <fstream>
#include <filesystem>

#include "../../Includes/Repository/containerrepository.h"
#include "../../Includes/Repository/sphererepository.h"

ConvectionCalculator::ConvectionCalculator(const ContainerRepository& ctr) {
    if (ctr.hasCones() > 0) {
        const auto cone = ctr.getCone();
        z_min = cone.getMin();
        z_max = cone.getMax();
        sectionSurface = cone.getSection();
    } else {
        std::tie(z_min, z_max, sectionSurface) = ctr.getBoxData();
        printf("BoxCase : (%e, %e, %e)\n", z_min, z_max, sectionSurface);
    }
}

void ConvectionCalculator::computeConvectionData(SphereRepository& sphr) {
    const int n = sphr.getN();
    double dz , radial;
    // Loop over spheres in the packing
    for (const auto& sphere : sphr) {
        // Loop over time capture
        for (int i = 1 ; i < n ; i++) {
            dz = sphere.get_z_at(i) - sphere.get_z_at(i-1);
            radial = sqrt(sphere.get_x_at(i-1)*sphere.get_x_at(i-1) + sphere.get_y_at(i-1)*sphere.get_y_at(i-1));
            verticalDisplacement.push_back(dz);
            radialPosition.push_back(radial);
        }
    }
}


void ConvectionCalculator::exportConvectionData(const std::string& directory) {
    namespace fs = std::filesystem;

    // Dossier cible : <directory>/PackingFraction
    const fs::path outDir = fs::path(directory) / "ConvectionData";

    std::error_code ec;
    fs::create_directories(outDir, ec);
    if (ec)
        throw std::runtime_error("Cannot create directory: " + outDir.string() + " (" + ec.message() + ")");

    const fs::path filePath = outDir / "convection_data.txt";
    std::ofstream ofs(filePath);
    if (!ofs)
        throw std::runtime_error("Cannot open file for writing: " + filePath.string());

    // Format numérique précis (utile si post-traitement scientifique)
    ofs << std::setprecision(17);

    for (std::size_t i = 0; i < verticalDisplacement.size(); ++i)
    {
        ofs << verticalDisplacement[i] << '\t' << radialPosition[i] << '\n';
    }
}
