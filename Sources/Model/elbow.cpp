#include "../../Includes/Model/elbow.h"

#include <limits>

#define N1 15
#define N2 15

Elbow::Elbow() {
    radius = 0.1;
}

void Elbow::ReadFromFile(FILE *ft)
{
    Velocity vx_loaded, vy_loaded, vz_loaded, wx_loaded, wy_loaded, wz_loaded;
    double xi_loaded, yi_loaded, zi_loaded;
    double xf_loaded, yf_loaded, zf_loaded;
    double xr_loaded, yr_loaded, zr_loaded;
    double nx_loaded, ny_loaded, nz_loaded;
    double tx_loaded, ty_loaded, tz_loaded;
    double sx_loaded, sy_loaded, sz_loaded;

    fscanf(ft,"%lf\t%lf\t%lf\n",&xi_loaded,&yi_loaded,&zi_loaded);
    fscanf(ft,"%lf\t%lf\t%lf\n",&xf_loaded,&yf_loaded,&zf_loaded);
    fscanf(ft,"%lf\t%lf\t%lf\n",&xr_loaded,&yr_loaded,&zr_loaded);
    fscanf(ft,"%lf\t%lf\t%lf\n",&nx_loaded,&ny_loaded,&nz_loaded);
    fscanf(ft,"%lf\t%lf\t%lf\n",&tx_loaded,&ty_loaded,&tz_loaded);
    fscanf(ft,"%lf\t%lf\t%lf\n",&sx_loaded,&sy_loaded,&sz_loaded);
    vx_loaded.ReadFromFile(ft);
    vy_loaded.ReadFromFile(ft);
    vz_loaded.ReadFromFile(ft);
    wx_loaded.ReadFromFile(ft);
    wy_loaded.ReadFromFile(ft);
    wz_loaded.ReadFromFile(ft);
    fscanf(ft,"%lf\t%lf\t%lf\n",&orx,&ory,&orz);
    fscanf(ft,"%lf\t%lf\t%lf\n",&Rc,&alpha,&radius);


    xi.push_back(xi_loaded);
    yi.push_back(yi_loaded);
    zi.push_back(zi_loaded);

    xf.push_back(xf_loaded);
    yf.push_back(yf_loaded);
    zf.push_back(zf_loaded);

    xr.push_back(xr_loaded);
    yr.push_back(yr_loaded);
    zr.push_back(zr_loaded);

    nx.push_back(nx_loaded);
    ny.push_back(ny_loaded);
    nz.push_back(nz_loaded);

    tx.push_back(tx_loaded);
    ty.push_back(ty_loaded);
    tz.push_back(tz_loaded);

    sx.push_back(sx_loaded);
    sy.push_back(sy_loaded);
    sz.push_back(sz_loaded);

    vx.push_back(vx_loaded);
    vy.push_back(vy_loaded);
    vz.push_back(vz_loaded);
    wx.push_back(wx_loaded);
    wy.push_back(wy_loaded);
    wz.push_back(wz_loaded);
}


bool Elbow::readFromStream(std::istream& in) {
    double xi_loaded, yi_loaded, zi_loaded;
    double xf_loaded, yf_loaded, zf_loaded;
    double xr_loaded, yr_loaded, zr_loaded;
    double nx_loaded, ny_loaded, nz_loaded;
    double tx_loaded, ty_loaded, tz_loaded;
    double sx_loaded, sy_loaded, sz_loaded;

    Velocity vx_loaded, vy_loaded, vz_loaded;
    Velocity wx_loaded, wy_loaded, wz_loaded;

    // Lecture des points
    if (!(in >> xi_loaded >> yi_loaded >> zi_loaded)) return false;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!(in >> xf_loaded >> yf_loaded >> zf_loaded)) return false;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!(in >> xr_loaded >> yr_loaded >> zr_loaded)) return false;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!(in >> nx_loaded >> ny_loaded >> nz_loaded)) return false;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!(in >> tx_loaded >> ty_loaded >> tz_loaded)) return false;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!(in >> sx_loaded >> sy_loaded >> sz_loaded)) return false;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Vitesses
    if (!vx_loaded.readFromStream(in)) return false;
    if (!vy_loaded.readFromStream(in)) return false;
    if (!vz_loaded.readFromStream(in)) return false;
    if (!wx_loaded.readFromStream(in)) return false;
    if (!wy_loaded.readFromStream(in)) return false;
    if (!wz_loaded.readFromStream(in)) return false;

    // Rotation
    if (!(in >> orx >> ory >> orz)) return false;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!(in >> Rc >> alpha >> radius)) return false;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Push dans les vecteurs
    xi.push_back(xi_loaded);  yi.push_back(yi_loaded);  zi.push_back(zi_loaded);
    xf.push_back(xf_loaded);  yf.push_back(yf_loaded);  zf.push_back(zf_loaded);
    xr.push_back(xr_loaded);  yr.push_back(yr_loaded);  zr.push_back(zr_loaded);

    nx.push_back(nx_loaded);  ny.push_back(ny_loaded);  nz.push_back(nz_loaded);
    tx.push_back(tx_loaded);  ty.push_back(ty_loaded);  tz.push_back(tz_loaded);
    sx.push_back(sx_loaded);  sy.push_back(sy_loaded);  sz.push_back(sz_loaded);

    vx.push_back(vx_loaded);  vy.push_back(vy_loaded);  vz.push_back(vz_loaded);
    wx.push_back(wx_loaded);  wy.push_back(wy_loaded);  wz.push_back(wz_loaded);

    return true;
}
