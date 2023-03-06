#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <tuple>
#include <utility>
#include <string>
#include "gnuplot_iostream.h"


//Cubic Bezier Curve

int main()
{
    Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\"");


    std::vector<std::pair<double, double>> v1;

    std::vector<double> xP{ 2.5, 1.5, 6.0, 10.0 };
    std::vector<double> yP{ 0.5, 5.0, 5.0, 0.5 };

    std::vector<std::pair<double, double>> v2;

    for (int i = 0; i < 20; i++)
    {
        double u = (double)i / 10;

        double x = xP[0] * (pow((1 - u), 3)) + xP[1] * (3 * pow((1 - u), 2) * (u)) + xP[2] * (3 * (u - 1) * pow((u), 2)) + xP[3] * (pow((u), 3));
        double y = yP[0] * (pow((1 - u), 3)) + yP[1] * (3 * pow((1 - u), 2) * (u)) + yP[2] * (3 * pow((u), 2) * (u - 1)) + yP[3] * (pow((u), 3));

        v1.push_back(std::make_pair(x, y));
    }


    gp << "set title 'Graph of bezier curve'\n";
    gp << "plot '-' with lp title 'v1'\n";

    gp.send(v1);

    std::cin.get();
}