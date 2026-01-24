#include "../../Includes/Model/plan.h"

#include </usr/include/GL/glu.h>
#include <limits>
#include <iostream>

Plan::Plan() : Solid() {
    dt = 0.5;
    ds = 0.5;
    ped = -9;
    inAndOut = 0;
}

void Plan::ReadFromFile(FILE *ft)
{
    double a;
    Solid::ReadFromFile(ft);
    fscanf(ft,"%lf\t%lf\t%lf\n%d\t%d\t%d\n",&a,&dt,&ds,&ped,&Ngb,&inAndOut);
}

bool Plan::readFromStream(std::istream& in) {
    double a = 0;

    // Lecture de la partie commune (héritée de Solid)
    if (!Solid::readFromStream(in)) {
        std::cerr << "Plan : erreur lors de la lecture de la partie Solid\n";
        return false;
    }

    // Lecture de la ligne contenant a, dt, ds
    if (!(in >> a >> dt >> ds)) {
        std::cerr << "Plan : erreur de lecture (a, dt, ds)\n";
        return false;
    }

    // Consomme le retour à la ligne
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Lecture de la ligne contenant ped, Ngb, inAndOut
    if (!(in >> ped >> Ngb >> inAndOut)) {
        std::cerr << "Plan : erreur de lecture (ped, Ngb, inAndOut)\n";
        return false;
    }

    // Consomme le retour à la ligne
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return true;
}