// SurfaceLoftApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
    double deltaX = (endPoint.dataPoints[0] - startPoint.dataPoints[0]) / (numU - 1);
    double deltaY = (endPoint.dataPoints[1] - startPoint.dataPoints[1]) / (numU - 1);
    double deltaZ = (endPoint.dataPoints[2] - startPoint.dataPoints[2]) / (numU - 1);

    for (int i = 0; i < numU; i++)
    {
        Point p;
        p.dataPoints[0] = startPoint.dataPoints[0] + i * deltaX;
        p.dataPoints[1] = startPoint.dataPoints[1] + i * deltaY;
        p.dataPoints[2] = startPoint.dataPoints[2] + i * deltaZ;
        line.push_back(p);
    }
}

void generateCircle(Point centerPoint, double numU, std::vector<Point>& circle)
{
    double theta = (2 * PI) / (numU * 4);

    double radius = 6;

    for (double u{ 0 }; u < 2 * PI; u += theta)
    {
        Point p;

        p.dataPoints[0] = radius * cos(u);
        p.dataPoints[1] = radius * sin(u);
        p.dataPoints[2] = 30.0;

        circle.emplace_back(p);
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

    //gp << "set grid\n";

    std::vector<std::tuple<double, double, double>> v;
    double arr[3];
    for (int i = 0; i < loftSurface.size(); ++i)
    {
        for (int j = 0; j < loftSurface[i].size(); ++j)
        {
            for (int k = 0; k < 3; ++k)
            {

                arr[k] = loftSurface[i][j].dataPoints[k];

            }
            v.emplace_back(std::make_tuple(arr[0], arr[1], arr[2]));
        }
    }

    gp << "set hidden3d\n";
    gp << "set xrange[-20:50]\n";
    gp << "set yrange[-20:30]\n";
    gp << "set zrange[-20:30]\n";
    gp << "set title 'Loft circle and square'\n";
    gp << "splot '-' with lines title 'v'\n";

    gp.send(v);
    std::cin.get();
}


int main()
{
    std::vector<Point> line;
    std::vector<Point> circle;

    Point p1 = {1.0, 1.0, 0.0};
    Point p2 = { 1.0, 10.0, 0.0 };
    Point p3 = { 10.0, 10.0, 0.0 };
    Point p4 = { 10.0, 1.0, 0.0 };

    Point centerPoint = { 8, 6, 80.0 };
    std::vector<std::vector<Point>> loftSurface;

    double numU{ 20 }, numV{ 50 };

    generateLine(p1, p2, numU, line);
    generateLine(p2, p3, numU, line);
    generateLine(p3, p4, numU, line);
    generateLine(p4, p1, numU, line);

    generateCircle(centerPoint, numU , circle);

    surfaceLoft(circle, line, numV, loftSurface);

    displayGNU(loftSurface);


    std::cin.get();
}
