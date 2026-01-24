#include "../../Includes/Model/disk.h"

#include <limits>
#include <iostream>

Disk::Disk() {
    r = 0.5;
}

void Disk::ReadFromFile(FILE *ft)
{
    double a;
    Solid::ReadFromFile(ft);
    fscanf(ft,"%lf\t%lf",&a,&r);
    fscanf(ft,"%d\t%d",&periodic,&Ngb);
}

bool Disk::readFromStream(std::istream& in) {
    double a = 0;

    std::cout << "Disk : Stream - " << &in << std::endl;

    // Partie héritée de Solid
    if (!Solid::readFromStream(in)) {
        std::cerr << "Disk : erreur lors de la lecture de la partie Solid\n";
        return false;
    }

    // Lecture des données spécifiques à Disk
    if (!(in >> a >> r)) {
        std::cerr << "Disk : erreur de lecture (a, r)\n";
        return false;
    }

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!(in >> periodic >> Ngb)) {
        std::cerr << "Disk : erreur de lecture (periodic, Ngb)\n";
        return false;
    }

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return true;
}


void Disk::Display() {
    Solid::Display();
    printf("(r) = (%e)\n\n", r);
}