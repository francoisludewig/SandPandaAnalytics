#include "../../Includes/Model/cone.h"

#include <limits>
#include <iostream>

Cone::Cone():Solid() {
    r0 = 0.25;
    r1 = 0.5;
    h = 0.75;
    dr = 0.25;
}

void Cone::ReadFromFile(FILE *ft)
{
    int b;
    Solid::ReadFromFile(ft);
    fscanf(ft,"%lf\t%lf\t%lf\t%lf",&h,&r0,&r1,&dr);
    fscanf(ft,"%d\t%d\t%d",&inte,&b,&Ngb);
}

bool Cone::readFromStream(std::istream& in) {
    int b = 0;

    // Lire la partie commune depuis la classe de base
    if (!Solid::readFromStream(in)) {
        std::cerr << "Erreur lors de la lecture de Solid depuis Cone\n";
        return false;
    }

    // Lecture des données spécifiques à Cone
    if (!(in >> h >> r0 >> r1 >> dr)) {
        std::cerr << "Erreur lecture des dimensions Cone\n";
        return false;
    }

    if (!(in >> inte >> b >> Ngb)) {
        std::cerr << "Erreur lecture des entiers Cone\n";
        return false;
    }

    // Consommer le retour à la ligne restant (si présent)
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return true;
}

void Cone::Display() {
    Solid::Display();

    printf("(h, r0, r1, dr) = (%e\t%e\t%e\t%e)\n\n",h,r0,r1,dr);
}