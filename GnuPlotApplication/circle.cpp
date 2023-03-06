#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <tuple>
#include <utility>
#include <string>
#include "gnuplot_iostream.h"

#define PI 3.1415926

//Circle

int main()
{
    Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\"");

    int noOfPoints = 50;
    double radius = 10;
    double delta = (2 * PI) / noOfPoints;

    std::vector<std::pair<double, double>> v2;

    for (double theta = 0; theta < 2 * PI; theta += delta)
    {
        double x = radius * cos(theta);
        double y = radius * sin(theta);

        v2.push_back(std::make_pair(x, y));
    }

    gp << "set title 'Graph of circle'\n";
    gp << "plot '-' with lp title 'v2'\n";

    gp.send(v2);

    std::cin.get();
}