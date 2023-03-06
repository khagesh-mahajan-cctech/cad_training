#include <iostream>
#include <vector>
#include <string>
#include "gnuplot_iostream.h"

#define PI 3.14159

struct Point
{
    double dataPoints[3] = { 0.0,0.0,0.0 };
};

void generateLine(Point startPoint, Point endPoint, int numU, std::vector<Point>& line)
{
    double deltaU = (endPoint.dataPoints[0] - startPoint.dataPoints[0]) / (numU - 1);

    for (int u = 0; u < numU; u++)
    {
        Point p;

        p.dataPoints[0] = startPoint.dataPoints[0] * (1 - deltaU) + deltaU * u;
        p.dataPoints[1] = startPoint.dataPoints[1] * (1 - deltaU) + deltaU * u;
        p.dataPoints[2] = startPoint.dataPoints[2] * (1 - deltaU) + deltaU * u;

        line.push_back(p);
    }
}

void generateBCurve(Point startPoint, Point secondPoint, Point thirdPoint, Point endPoint, int numU, std::vector<Point>& bezierCurve)
{
    double deltaU = 1.0 / (numU - 1);

    for (double u = 0; u <= 1.0; u += deltaU)
    {

        Point p;
        p.dataPoints[0] = startPoint.dataPoints[0] * (pow((1 - u), 3)) + secondPoint.dataPoints[0] * (3 * pow((1 - u), 2) * (u)) + thirdPoint.dataPoints[0] * (3 * pow((u), 2) * (u - 1)) + endPoint.dataPoints[0] * (pow((u), 3));
        p.dataPoints[1] = startPoint.dataPoints[1] * (pow((1 - u), 3)) + secondPoint.dataPoints[1] * (3 * pow((1 - u), 2) * (u)) + thirdPoint.dataPoints[1] * (3 * pow((u), 2) * (u - 1)) + endPoint.dataPoints[1] * (pow((u), 3));
        p.dataPoints[2] = startPoint.dataPoints[2] * (pow((1 - u), 3)) + secondPoint.dataPoints[2] * (3 * pow((1 - u), 2) * (u)) + thirdPoint.dataPoints[2] * (3 * pow((u), 2) * (u - 1)) + endPoint.dataPoints[2] * (pow((u), 3)) + 20;

        bezierCurve.push_back(p);
    }
}


bool surfaceLoft(std::vector<Point>& c1, std::vector<Point>& c2, double numV, std::vector<std::vector<Point>>& loftSurface)
{
    if (c1.size() != c2.size())
        return false;

    double deltaV = 1.0 / (numV - 1);

    std::vector<Point> c;

    c.resize(c1.size());

    for (double v = 0; v <= 1.0; v += deltaV)
    {
        for (int i = 0; i < c1.size(); i++)
        {
            for (int j = 0; j < 3; j++) {
                c[i].dataPoints[j] = c1[i].dataPoints[j] * (1 - v) + c2[i].dataPoints[j] * v;
            }
        }
        loftSurface.push_back(c);
    }

    return true;
}

void displayGNU(std::vector<std::vector<Point>>& loftSurface)
{
    Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\"");

    std::vector<std::tuple<double, double, double>> loft;
    double arr[3];

    for (int i = 0; i < loftSurface.size(); ++i)
    {
        for (int j = 0; j < loftSurface[i].size(); ++j)
        {
            for (int k = 0; k < 3; ++k)
            {

                arr[k] = loftSurface[i][j].dataPoints[k];

            }
            loft.emplace_back(std::make_tuple(arr[0], arr[1], arr[2]));
        }
    }

    gp << "set hidden3d\n";
    gp << "set xrange[-2:3]\n";
    gp << "set yrange[-2:3]\n";
    gp << "set zrange[-2:10]\n";
    gp << "set title 'Loft bezier curve and line'\n";
    gp << "splot '-' with lp title 'loft'\n";

    gp.send(loft);
    std::cin.get();
}


int main()
{
    std::vector<Point> line;
    Point startPoint = {0,0,0};
    Point secondPoint = { 2,20,5 };
    Point thirdPoint = { 6,20,5 };
    Point endPoint = { 10,10,0 };

    std::vector<Point> bCurve;
    std::vector<std::vector<Point>> loftSurface;

    double numU{ 30 }, numV{ 100 };

    generateLine(startPoint, endPoint, numU, line);
    generateBCurve(startPoint, secondPoint, thirdPoint, endPoint, numU, bCurve);

    surfaceLoft(line, bCurve, numV, loftSurface);

    displayGNU(loftSurface);

    std::cin.get();
}