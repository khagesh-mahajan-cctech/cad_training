#include <iostream>
#include <vector>
#include <string>
#include "gnuplot_iostream.h"

#define PI 3.14159

struct Point
{
    double dataPoints[3] = { 0.0,0.0,0.0 };
};

typedef std::vector<Point> Curve;
typedef std::vector<Curve> Surface;

void generateConics(Point centerPoint, double radiusA, double radiusB, int numU, Curve& curve)
{
    double theta = (2 * PI) / numU;

    double radius = 100;

    for (double u{ 0 }; u < 2 * PI; u += theta)
    {
        Point p;

        p.dataPoints[0] = (centerPoint.dataPoints[0] + radius) * cos(u);
        p.dataPoints[1] = (centerPoint.dataPoints[1] + radius) * sin(u);
        p.dataPoints[2] = centerPoint.dataPoints[2];

        curve.emplace_back(p);
    }
}

bool generateSurfaceLoft(Curve& c1, Curve& c2, int numV, Surface& loftSurface)
{
    if (c1.size() != c2.size())
        return false;

    double deltaV = 1.0 / (numV - 1);

    Curve c;
    c.resize(c1.size());

    for (double v = 0; v <= 1.0; v += deltaV)
    {
        for (int i = 0; i < c1.size(); i++) 
        {
            for (int j = 0; j < 3; j++) 
            {
                c[i].dataPoints[j] = c1[i].dataPoints[j] * (1 - v) + c2[i].dataPoints[j] * v;
            }
        }

        loftSurface.push_back(c);
    }

    return true;
}

void displayGNU(std::vector<Surface>& loftSurface)
{
    Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\"");

    //gp << "set grid\n";

    std::vector<std::tuple<double, double, double>> v;
    double arr[3];

    for (int i = 0; i < loftSurface.size(); ++i)
    {
        for (int j = 0; j < loftSurface[i].size(); ++j)
        {
            for (int k = 0; k < loftSurface[j].size(); ++k)
            {
                for (int m = 0; m < 3; ++m)
                {

                    arr[m] = loftSurface[i][j][k].dataPoints[m];

                }
                v.emplace_back(std::make_tuple(arr[0], arr[1], arr[2]));
            }
        }
    }

    //gp << "set hidden3d\n";
    gp << "set xrange[-50:200]\n";
    gp << "set yrange[-50:200]\n";
    gp << "set zrange[-50:300]\n";
    gp << "set title 'Bottle'\n";
    gp << "splot '-' with lines title 'v'\n";

    gp.send(v);
    std::cin.get();
}

int main()
{
    std::vector<Curve> sections;
    std::vector<Surface> surfacePatch;

    sections.resize(10);
    surfacePatch.resize(9);

    int index{ 0 };

    generateConics(Point{ 0.0,0.0,0.0 }, 0, 0, 72, sections[index]);
    generateConics(Point{ 0.0,0.0,0.0 }, 30, 30, 72, sections[index + 1]);
    generateSurfaceLoft(sections[index], sections[index + 1], 10, surfacePatch[index]);

    index++;

    generateConics(Point{ 0.0,0.0,12.0 }, 40, 40, 72, sections[index]);
    generateSurfaceLoft(sections[index], sections[index + 1], 10, surfacePatch[index]);

    index++;

    generateConics(Point{ 0.0,0.0,170.0 }, 40, 40, 72, sections[index]);
    generateSurfaceLoft(sections[index], sections[index + 1], 10, surfacePatch[index]);

    index++;

    generateConics(Point{ 0.0,0.0,230.0 }, 20, 20, 72, sections[index]);
    generateSurfaceLoft(sections[index], sections[index + 1], 10, surfacePatch[index]);

    index++;

    generateConics(Point{ 0.0,0.0,290.0 }, 20, 20, 72, sections[index]);
    generateSurfaceLoft(sections[index], sections[index + 1], 10, surfacePatch[index]);

    displayGNU(surfacePatch);

}