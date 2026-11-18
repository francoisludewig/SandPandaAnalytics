#include "../../Includes/Repository/containerrepository.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <limits>

ContainerRepository::ContainerRepository() {}

void ContainerRepository::load(std::string directory)
{
    namespace fs = std::filesystem;

    N = 0;
    plans.clear();
    disks.clear();
    cones.clear();
    elbows.clear();

    while (true) {
        fs::path filePath = fs::path(directory) / "Out" / ("container_" + std::to_string(N) + ".txt");

        std::ifstream file(filePath);
        if (!file.is_open())
            break;

        std::cout << "Loading file: " << filePath << "\n";

        int Nplan = 0, Ndisk = 0, Ncone = 0, Nelbow = 0;
        file >> Nplan >> Ndisk >> Ncone >> Nelbow;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip remaining of line

        if (N == 0) {
            for (int i = 0; i < Nplan; ++i) {
                Plan plan;
                if (!plan.readFromStream(file))
                    std::cerr << "Error reading plan " << i << " in file " << filePath << "\n";
                plans.push_back(plan);
            }

            for (int i = 0; i < Ndisk; ++i) {
                Disk disk;
                if (!disk.readFromStream(file))
                    std::cerr << "Error reading disk " << i << " in file " << filePath << "\n";
                disks.push_back(disk);
            }

            for (int i = 0; i < Ncone; ++i) {
                Cone cone;
                if (!cone.readFromStream(file))
                    std::cerr << "Error reading cone " << i << " in file " << filePath << "\n";
                cones.push_back(cone);
            }

            for (int i = 0; i < Nelbow; ++i) {
                Elbow elbow;
                if (!elbow.readFromStream(file))
                    std::cerr << "Error reading elbow " << i << " in file " << filePath << "\n";
                elbows.push_back(elbow);
            }
        } else {
            for (int i = 0; i < Nplan && i < static_cast<int>(plans.size()); ++i)
                plans[i].readFromStream(file);

            for (int i = 0; i < Ndisk && i < static_cast<int>(disks.size()); ++i)
                disks[i].readFromStream(file);

            for (int i = 0; i < Ncone && i < static_cast<int>(cones.size()); ++i)
                cones[i].readFromStream(file);

            for (int i = 0; i < Nelbow && i < static_cast<int>(elbows.size()); ++i)
                elbows[i].readFromStream(file);
        }

        ++N;
    }

    std::cout << N << " files found and loaded.\n";
}

std::tuple<double, double, double> ContainerRepository::getBoxData() const {
    double minxBox = 1000, minyBox = 1000, minzBox = 1000;
    double maxxBox = -1000, maxyBox = -1000, maxzBox = -1000;
    for (const auto& plan : plans) {
        auto [minx, miny, minz] = plan.getMin();
        auto [maxx, maxy, maxz] = plan.getMax();
        if (minx < minxBox) minxBox = minx;
        if (miny < minyBox) minyBox = miny;
        if (minz < minzBox) minzBox = minz;
        if (maxx > maxxBox) maxxBox = maxx;
        if (maxy > maxyBox) maxyBox = maxy;
        if (maxz > maxzBox) maxzBox = maxz;
    }

    return {minzBox, maxzBox, (maxxBox-minxBox)*(maxyBox-minyBox)};
}
