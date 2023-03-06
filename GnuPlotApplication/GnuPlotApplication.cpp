#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <tuple>
#include <utility>
#include <string>
#include "gnuplot_iostream.h"


//Line

int main()
{
    Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\"");

    std::vector<std::pair<double, double>> v1;
    std::vector<std::pair<double, double>> v2;

    double xCord;
    double yCord;

    std::vector<double> x{ 2, 1.5};
    std::vector<double> y{ 0.5, 5};

    for (double u = 0.1; u <= 1; u += 0.1)
    {
        xCord = x[0] * (1 - u) + x[1] * u;
        yCord = y[0] * (1 - u) + y[1] * u;

        v1.push_back(std::make_pair(xCord, yCord));
    }

    v2.push_back(std::make_pair(x[0], y[0]));
    v2.push_back(std::make_pair(x[1], y[1]));


    gp << "set title 'Graph of line'\n";
    gp << "plot '-' with lp title 'v1',"
        << "'-' with lines title 'v2'\n";

    gp.send(v1);
    gp.send(v2);

    std::cin.get();
}
