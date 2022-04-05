#include "Auxil.h"

std::random_device rd;
std::mt19937 mt(rd());

double Auxil::dget(double rmin, double rmax)
{
    std::uniform_real_distribution<double> dist(rmin, rmax);
    return dist(mt);
}

int Auxil::iget(int rmin, int rmax)
{
    std::uniform_real_distribution<float> dist(rmin, rmax);
    return static_cast<int>(dist(mt));
}