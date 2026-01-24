#include "../../Includes/Model/solid.h"
#include <limits>
#include <iostream>
Solid::Solid() {}

void Solid::ReadFromFile(FILE *ft)
{
    double x_loaded = 0, y_loaded = 0, z_loaded = 0;
    double q0 = 0,q1 = 1,q2 = 0,q3 = 0;
    int readed_count;
    Velocity vx_loaded, vy_loaded, vz_loaded, wx_loaded, wy_loaded, wz_loaded;

    readed_count = std::fscanf(ft, "%lf %lf %lf",&x_loaded,&y_loaded,&z_loaded);
    if(readed_count != 3) {
        char buffer[256];
        fscanf(ft,"%[^\n]", buffer);
        printf("Solid : fscanf failed (%d) - %s\n", readed_count,buffer);
        fflush(stdout);
        return;
    }
    fscanf(ft, "%lf\t%lf\t%lf\t%lf",&q0,&q1,&q2,&q3);
    vx_loaded.ReadFromFile(ft);
    vy_loaded.ReadFromFile(ft);
    vz_loaded.ReadFromFile(ft);
    wx_loaded.ReadFromFile(ft);
    wy_loaded.ReadFromFile(ft);
    wz_loaded.ReadFromFile(ft);
    fscanf(ft, "%lf\t%lf\t%lf",&orx,&ory,&orz);

    printf("Loaded value : (%e\t%e\t%e)\n",x_loaded,y_loaded,z_loaded);
    printf("Loaded value q : (%e\t%e\t%e\t%e)\n",q0,q1,q2,q3);

    x.push_back(x_loaded);
    y.push_back(y_loaded);
    z.push_back(z_loaded);

    nx.push_back(1 - 2*q2*q2 - 2*q3*q3);
    ny.push_back(2*q1*q2 + 2*q3*q0);
    nz.push_back(2*q1*q3 - 2*q2*q0);

    tx.push_back(2*q1*q2 - 2*q3*q0);
    ty.push_back(1 - 2*q1*q1 - 2*q3*q3);
    tz.push_back(2*q2*q3 + 2*q1*q0);

    sx.push_back(2*q1*q3 + 2*q2*q0);
    sy.push_back(2*q2*q3 - 2*q1*q0);
    sz.push_back(1 - 2*q1*q1 - 2*q2*q2);

    vx.push_back(vx_loaded);
    vy.push_back(vy_loaded);
    vz.push_back(vz_loaded);
    wx.push_back(wx_loaded);
    wy.push_back(wy_loaded);
    wz.push_back(wz_loaded);
}


bool Solid::readFromStream(std::istream& in) {
    double x_loaded = 0, y_loaded = 0, z_loaded = 0;
    double q0 = 0, q1 = 1, q2 = 0, q3 = 0;

    Velocity vx_loaded, vy_loaded, vz_loaded;
    Velocity wx_loaded, wy_loaded, wz_loaded;

    // Lecture position
    if (!(in >> x_loaded >> y_loaded >> z_loaded)) {
        std::cerr << "Solid : erreur de lecture des coordonnées (x, y, z)\n";
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    // Lecture quaternion
    if (!(in >> q0 >> q1 >> q2 >> q3)) {
        std::cerr << "Solid : erreur de lecture du quaternion\n";
        return false;
    }

    // Lecture vitesses linéaires
    if (!vx_loaded.readFromStream(in) || !vy_loaded.readFromStream(in) || !vz_loaded.readFromStream(in)) {
        std::cerr << "Solid : erreur de lecture des vitesses linéaires\n";
        return false;
    }

    // Lecture vitesses angulaires
    if (!wx_loaded.readFromStream(in) || !wy_loaded.readFromStream(in) || !wz_loaded.readFromStream(in)) {
        std::cerr << "Solid : erreur de lecture des vitesses angulaires\n";
        return false;
    }

    // Lecture orientation finale
    if (!(in >> orx >> ory >> orz)) {
        std::cerr << "Solid : erreur de lecture de l'orientation (orx, ory, orz)\n";
        return false;
    }

    // Ajout aux vecteurs membres
    x.push_back(x_loaded);
    y.push_back(y_loaded);
    z.push_back(z_loaded);

    // Quaternion → axes de rotation
    nx.push_back(1 - 2 * q2 * q2 - 2 * q3 * q3);
    ny.push_back(2 * q1 * q2 + 2 * q3 * q0);
    nz.push_back(2 * q1 * q3 - 2 * q2 * q0);

    tx.push_back(2 * q1 * q2 - 2 * q3 * q0);
    ty.push_back(1 - 2 * q1 * q1 - 2 * q3 * q3);
    tz.push_back(2 * q2 * q3 + 2 * q1 * q0);

    sx.push_back(2 * q1 * q3 + 2 * q2 * q0);
    sy.push_back(2 * q2 * q3 - 2 * q1 * q0);
    sz.push_back(1 - 2 * q1 * q1 - 2 * q2 * q2);

    vx.push_back(vx_loaded);
    vy.push_back(vy_loaded);
    vz.push_back(vz_loaded);
    wx.push_back(wx_loaded);
    wy.push_back(wy_loaded);
    wz.push_back(wz_loaded);

    return true;
}

void Solid::Display() {
    printf("(x, y, z) = (%e, %e, %e)\n" , x[0], y[0], z[0]);
    printf("(nx, ny, nz) = (%e, %e, %e)\n" , nx[0], ny[0], nz[0]);
}
