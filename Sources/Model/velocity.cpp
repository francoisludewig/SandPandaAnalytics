#include "../../Includes/Model/velocity.h"
#include <limits>
#include <iostream>

Velocity::Velocity() {
    A0 = 0;
    A1 = 0;
    w = 0;
    p = 0;}

void Velocity::ReadFromFile(FILE *ft)
{
    fscanf(ft,"%lf\t%lf\t%lf\t%lf\n",&A0,&A1,&w,&p);
}

bool Velocity::readFromStream(std::istream& in) {
    if (!(in >> A0 >> A1 >> w >> p)) {
        std::cerr << "Velocity : erreur de lecture (A0, A1, w, p)\n";
        return false;
    }

    // Consomme le retour à la ligne
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return true;
}
