//
// Created by ludfr on 27/02/2026.
//

#include "../../Includes/PackingFraction/PackingFractionProfileCalculator.h"

#include <fstream>
#include <iomanip>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include "../../Includes/Repository/containerrepository.h"
#include "../../Includes/Repository/sphererepository.h"

namespace {
    bool isFinite(double x) { return std::isfinite(x); }

    // Médiane d'un vecteur (copie) ; O(n) via nth_element
    double medianOf(std::vector<double> v)
    {
        if (v.empty()) return std::numeric_limits<double>::quiet_NaN();

        const std::size_t n = v.size();
        const std::size_t mid = n / 2;

        std::nth_element(v.begin(), v.begin() + mid, v.end());
        double m = v[mid];

        if (n % 2 == 0) {
            // pour n pair, prendre moyenne des deux valeurs centrales
            const auto max_it = std::max_element(v.begin(), v.begin() + mid);
            m = (m + *max_it) * 0.5;
        }
        return m;
    }
}

PackingFractionProfileCalculator::PackingFractionProfileCalculator(ContainerRepository& ctr) {
    if (ctr.hasCones() > 0) {
        auto cone = ctr.getCone();
        z_min = cone.getMin();
        z_max = cone.getMax();
        sectionSurface = cone.getSection();
    } else {
        //TODO Analyse Box case
        z_min = 0;
        z_max = 0;
        sectionSurface = 0;
    }
}

void PackingFractionProfileCalculator::computePackingFractionProfile(SphereRepository& sphr) {
    scale = sphr.minimal_radius()/10;
    int step_count = (int) ((z_max - z_min)/scale) + 1;
    double current_z;

    int n = sphr.getN();
    // Loop over time capture
    for (int i = 0 ; i < n ; i++) {
        std::vector<double> profile_at(step_count);
        for (int j = 0 ; j < step_count ; j++)
            profile_at[j] = 0;
        // Loop over spheres in the packing
        for (const auto& sphere : sphr) {
            // Loop over the step
            for (int j = 0 ; j < step_count ; j++) {
                current_z = z_min + j*scale;
                if (abs(current_z - sphere.get_z_at(i)) < sphere.getRadius()) {
                    profile_at[j] += M_PI * (sphere.getRadius()*sphere.getRadius() - (current_z - sphere.get_z_at(i))*(current_z - sphere.get_z_at(i)));
                }
            }
        }
        for (int j = 0 ; j < step_count ; j++)
            profile_at[j] /= sectionSurface;
        profiles.push_back(profile_at);
    }
}

void PackingFractionProfileCalculator::computePackingFraction() {
    packingFractions.clear();
    packingFractions.reserve(profiles.size());

    // paramètres (à ajuster)
    const double ignoreBottomFrac = 0.10; // ignore 10% du bas
    const double ignoreTopFrac    = 0.10; // ignore 10% du haut
    const double clampMin = 0.0;          // packing fraction physiquement >= 0
    const double clampMax = 1.0;          // et <= 1 (souvent)

    for (const auto& profile : profiles)
    {
        if (profile.empty()) {
            packingFractions.push_back(std::numeric_limits<double>::quiet_NaN());
            continue;
        }

        // 1) on coupe les bords en z
        const std::size_t n = profile.size();
        std::size_t i0 = static_cast<std::size_t>(std::floor(ignoreBottomFrac * n));
        std::size_t i1 = n - static_cast<std::size_t>(std::floor(ignoreTopFrac * n));
        i0 = std::min(i0, n);
        i1 = std::min(std::max(i1, i0), n);

        std::vector<double> core;
        core.reserve(i1 - i0);

        // 2) on filtre les valeurs non finies et on clamp
        for (std::size_t i = i0; i < i1; ++i) {
            double v = profile[i];
            if (!isFinite(v)) continue;
            v = std::clamp(v, clampMin, clampMax);
            core.push_back(v);
        }

        if (core.empty()) {
            packingFractions.push_back(std::numeric_limits<double>::quiet_NaN());
            continue;
        }

        // 3) médiane de la zone centrale
        const double pf = medianOf(core);
        packingFractions.push_back(pf);
    }
}

void PackingFractionProfileCalculator::exportProfiles(const std::string& directory) {
    namespace fs = std::filesystem;

    // Dossier cible : <directory>/PackingFraction
    const fs::path baseDir(directory);
    const fs::path outDir = baseDir / "PackingFraction";

    // Création (idempotente)
    std::error_code ec;
    fs::create_directories(outDir, ec);
    if (ec)
        throw std::runtime_error("Cannot create directory: " + outDir.string() + " (" + ec.message() + ")");

    // Ecriture de profile_#.txt
    for (std::size_t p = 0; p < profiles.size(); ++p)
    {
        const fs::path filePath = outDir / ("profile_" + std::to_string(p) + ".txt");
        std::ofstream ofs(filePath);
        if (!ofs)
            throw std::runtime_error("Cannot open file for writing: " + filePath.string());

        // Optionnel: format stable
        ofs << std::setprecision(17);

        const auto& prof = profiles[p];
        for (std::size_t i = 0; i < prof.size(); ++i)
        {
            const double z = z_min + static_cast<double>(i) * scale;
            ofs << z << '\t' << prof[i] << '\n';
        }
    }
}

void PackingFractionProfileCalculator::exportPackingFractions(const std::string& directory) {
    namespace fs = std::filesystem;

    // Dossier cible : <directory>/PackingFraction
    const fs::path outDir = fs::path(directory) / "PackingFraction";

    std::error_code ec;
    fs::create_directories(outDir, ec);
    if (ec)
        throw std::runtime_error("Cannot create directory: " + outDir.string() + " (" + ec.message() + ")");

    const fs::path filePath = outDir / "packing_fraction.txt";
    std::ofstream ofs(filePath);
    if (!ofs)
        throw std::runtime_error("Cannot open file for writing: " + filePath.string());

    // Format numérique précis (utile si post-traitement scientifique)
    ofs << std::setprecision(17);

    for (std::size_t i = 0; i < packingFractions.size(); ++i)
    {
        ofs << i << '\t' << packingFractions[i] << '\n';
    }
}
