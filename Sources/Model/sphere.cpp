#include "../../Includes/Model/sphere.h"

#include <istream>
#include <vector>
#include <iostream>
#include <sstream>

Sphere::Sphere() {}

void Sphere::ReadFromFile(FILE *ft)
{
    int b = 0,b1 = 0;
    double q0 = 0,q1 = 1,q2 = 0,q3 = 0;
    int sp_loaded = 0;
    double r_loaded = 0;
    double x_loaded = 0;
    double y_loaded = 0;
    double z_loaded = 0;
    double vx_loaded = 0;
    double vy_loaded = 0;
    double vz_loaded = 0;
    double wx_loaded = 0;
    double wy_loaded = 0;
    double wz_loaded = 0;


    if(fscanf(ft,"%d\t%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%d\t%d\n",
             &b,&sp_loaded,&r_loaded,
             &x_loaded,&y_loaded,&z_loaded,
             &q0,&q1,&q2,&q3,
             &vx_loaded,&vy_loaded,&vz_loaded,
             &wx_loaded,&wy_loaded,&wz_loaded,
               &b,&b1) != 18) printf("Sphere : fscanf Error");

    sp.push_back(sp_loaded);
    r.push_back(r_loaded);
    x.push_back(x_loaded);
    y.push_back(y_loaded);
    z.push_back(z_loaded);
    vx.push_back(vx_loaded);
    vy.push_back(vy_loaded);
    vz.push_back(vz_loaded);
    wx.push_back(wx_loaded);
    wy.push_back(wy_loaded);
    wz.push_back(wz_loaded);

    // Quaternion -> axe de rotation et angle
    if(q0 != 0){
        nx.push_back(1 - 2*q2*q2 - 2*q3*q3);
        ny.push_back(2*q1*q2 + 2*q3*q0);
        nz.push_back(2*q1*q3 - 2*q2*q0);

        tx.push_back(2*q1*q2 - 2*q3*q0);
        ty.push_back(1 - 2*q1*q1 - 2*q3*q3);
        tz.push_back(2*q2*q3 + 2*q1*q0);

        sx.push_back(2*q1*q3 + 2*q2*q0);
        sy.push_back(2*q2*q3 - 2*q1*q0);
        sz.push_back(1 - 2*q1*q1 - 2*q2*q2);
    }
    else{
        nx.push_back(1);
        ny.push_back(0);
        nz.push_back(0);
        tx.push_back(0);
        ty.push_back(1);
        tz.push_back(0);
        sx.push_back(0);
        sy.push_back(0);
        sz.push_back(1);
    }
    if(b1 != -9)bd = true;
}



bool Sphere::readFromStream(std::istream& in) {
    int b = 0, b1 = 0;
    double q0 = 0, q1 = 1, q2 = 0, q3 = 0;
    int sp_loaded = 0;
    double r_loaded = 0;
    double x_loaded = 0, y_loaded = 0, z_loaded = 0;
    double vx_loaded = 0, vy_loaded = 0, vz_loaded = 0;
    double wx_loaded = 0, wy_loaded = 0, wz_loaded = 0;

    std::string line;
    if (!std::getline(in, line)) return false;

    std::istringstream iss(line);
    if (!(iss >> b >> sp_loaded >> r_loaded
          >> x_loaded >> y_loaded >> z_loaded
          >> q0 >> q1 >> q2 >> q3
          >> vx_loaded >> vy_loaded >> vz_loaded
          >> wx_loaded >> wy_loaded >> wz_loaded
          >> b >> b1)) {
        std::cerr << "Sphere: parsing error in line: " << line << "\n";
        return false;
    }

    sp.push_back(sp_loaded);
    r.push_back(r_loaded);
    x.push_back(x_loaded); y.push_back(y_loaded); z.push_back(z_loaded);
    vx.push_back(vx_loaded); vy.push_back(vy_loaded); vz.push_back(vz_loaded);
    wx.push_back(wx_loaded); wy.push_back(wy_loaded); wz.push_back(wz_loaded);

    if (q0 != 0) {
        nx.push_back(1 - 2*q2*q2 - 2*q3*q3);
        ny.push_back(2*q1*q2 + 2*q3*q0);
        nz.push_back(2*q1*q3 - 2*q2*q0);

        tx.push_back(2*q1*q2 - 2*q3*q0);
        ty.push_back(1 - 2*q1*q1 - 2*q3*q3);
        tz.push_back(2*q2*q3 + 2*q1*q0);

        sx.push_back(2*q1*q3 + 2*q2*q0);
        sy.push_back(2*q2*q3 - 2*q1*q0);
        sz.push_back(1 - 2*q1*q1 - 2*q2*q2);
    } else {
        nx.push_back(1); ny.push_back(0); nz.push_back(0);
        tx.push_back(0); ty.push_back(1); tz.push_back(0);
        sx.push_back(0); sy.push_back(0); sz.push_back(1);
    }

    if (b1 != -9) bd = true;
    return true;
}