#ifndef PLAN_H
#define PLAN_H

#include "solid.h"
#include<cstdio>

class Plan : Solid
{
public:
    Plan();
    void ReadFromFile(FILE *ft) override;
    bool readFromStream(std::istream& in) override;
    [[nodiscard]] std::tuple<double, double, double> getMin() const;
    [[nodiscard]] std::tuple<double, double, double> getMax() const;


private:
    double dt,ds;
    int ped;
    int inAndOut;
};

#endif // PLAN_H
