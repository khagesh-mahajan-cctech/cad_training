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

void generateCircle(Point centerPoint, double radius, double numU, std::vector<Point>& circle)
{
    double theta = (2 * PI) / numU;

    for (double u{ 0 }; u < 2 * PI; u += theta)
    {
        Point p;

        p.dataPoints[0] = radius * cos(u);
        p.dataPoints[1] = radius * sin(u);
        p.dataPoints[2] = 200.0;

        circle.emplace_back(p);
    }
}

void generateEllipse(Point centerPoint, double radiusA, double radiusB, double numU, std::vector<Point>& ellipse)
{
    double theta = (2 * PI) / numU;



    for (double u{ 0 }; u < 2 * PI; u += theta)
    {

        Point p;

        p.dataPoints[0] = radiusA * cos(u);
        p.dataPoints[1] = radiusB * sin(u);
        p.dataPoints[2] = -10.0;

        ellipse.emplace_back(p);
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
    gp << "set xrange[-30:50]\n";
    gp << "set yrange[-30:50]\n";
    gp << "set zrange[-30:50]\n";
    gp << "set title 'Graph of loft circle and ellipse'\n";
    gp << "splot '-' with lines title 'v'\n";

    gp.send(v);
    std::cin.get();
}


int main()
{
    std::vector<Point> circle;
    std::vector<Point> ellipse;

    std::vector<std::vector<Point>> loftSurface;

    double radius{ 50 }, radiusA{ 10 }, radiusB{ 20 };

    double numU{ 100 }, numV{ 200 };

    generateCircle(Point{ 0.0,0.0,0.0 }, radius, numU, circle);
    generateEllipse(Point{ 0.0,0.0,0.0 }, radiusA, radiusB, numU, ellipse);

    surfaceLoft(circle, ellipse, numV, loftSurface);

    displayGNU(loftSurface);

    for (int i = 0; i < loftSurface.size(); ++i)
    {
        for (int j = 0; j < loftSurface[i].size(); ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                std::cout << loftSurface[i][j].dataPoints[k] << "  ";
            }
            std::cout << std::endl;
        }
        std::cout << "\n------------------------------------" << std::endl;
    }

    std::cin.get();
}



















/*
struct Point
{
    double dataPoints[3] = { 0.0,0.0,0.0 };
};

typedef std::vector<Point> Curve;
typedef std::vector<Curve > Surface;

void generateCircle(Point centerPoint, double radius, double numU, Curve& circle)
{
    double theta = (2 * PI) / numU;

    for (double u{ 0 }; u < theta; ++u)
    {
        Point p;

        p.dataPoints[0] = radius * cos(u);
        p.dataPoints[1] = radius * sin(u);

        circle.emplace_back(p);
    }
}

void generateEllipse(Point centerPoint, double radiusA, double radiusB, double numU, Curve& ellipse)
{
    double theta = (2 * PI) / numU;

    for (double u{ 0 }; u < theta; ++u)
    {

        Point p;

        p.dataPoints[0] = radiusA * cos(u);
        p.dataPoints[1] = radiusB * sin(u);

        ellipse.emplace_back(p);
    }


}

bool surfaceLoft(Curve& c1, Curve& c2, double numV, Surface& loftSurface)
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
            for (int j = 0; j < 3; j++) {
                c[i].dataPoints[j] = c1[i].dataPoints[j] * (1 - v) + c2[i].dataPoints[j] * v;
            }
        }

        loftSurface.emplace_back(c);
    }

    return true;
}

void displayGNU(Surface& loftSurface)
{
    Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\"");

    //gp << "set grid\n";

    gp << "set hidden3d\n";
    gp << "set title 'Graph of loft surface'\n";
    gp << "splot '-' with lp title 'loftSurface'\n";

    gp.send(loftSurface);

}

int main()
{
    Curve circle;
    Curve ellipse;
    std::tuple<std::vector<double>, std::vector<double>> v1;

    std::vector<std::vector<Point>> v;

    Surface loftSurface;

    double radius{20}, radiusA{ 30 }, radiusB{ 30 };
    Curve centerPoint;
    double numU{ 72 }, numV{ 10 };

    generateCircle(Point{ 0.0,0.0,0.0 }, radius, numU, circle);
    generateEllipse(Point{ 0.0,0.0,0.0 }, radiusA, radiusB, numU, ellipse);
    surfaceLoft(circle, ellipse, numV, loftSurface);
    displayGNU(loftSurface);

    std::cin.get();
}

*/

























/*
#define _USE_MATH_DEFINES #include <iomanip>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream> using namespace std;
struct Point
{
    double data[3];
};
typedef vector<Point> Curve;
typedef vector<Curve > Surface; 

bool surfaceLoft(Curve c1, Curve c2, int numV, Surface loftSurface) 
{
    if (c1.size()!= c2.size())
        return false;     double  deltaV = 1.0 / (numV);
    for (double v = 0; v <= 1.0;v+=deltaV) 
    {
        Curve c;
        c.resize(c1.size());
        for (int i = 0; i < c1.size(); i++) {
            for (int j = 0; j < 3; j++) 
                c[i].data[j] = c1[i].data[j] * (1 - v) + c2[i].data[j] * v;
        }
        loftSurface.push_back(c);
    }
    return true;
} 


int main()
{
    Curve circle;
    Curve ellipse;
    int numU, numV;
    // input from user       
    generateCircle(centrePoint, radius, numU, circle);
    generateEllipse(centrePoint, radiusA, radiusB, numU, ellipse);     
    surfaceLoft(circle, ellipse, numV, loftSurface);     
    displayGNU(loftSurface);     
    return 1;
}
*/



/*
// AdvanceSurfaceLoft.cpp : This file contains the 'main' function. Program execution begins and ends there.
// #define _USE_MATH_DEFINES 
#include "stdafx.h"
using namespace std; 

struct GVector
{
    double data[3] = { 0.0,0.0,0.0 };
};

typedef vector<GVector> Curve;
typedef vector<Curve > Surface; 

std::string base_name(std::string const& path)
{
    return path.substr(path.find_last_of("/\\") + 1);
}

generateConics(GVector{ 0.0,0.0,0.0 }, 0, 0, 72, sections[index]); 
    generateConics(GVector{ 0.0,0.0,0.0 }, 30, 30, 72, sections[index+1]);

bool generateConics(GVector centrePoint, double radiusA, double radiusB, int numU, Curve& curve)
{
} 

bool writeGNU(Surface loftSurface, string filename)
{
    ofstream outFileHandle;
    outFileHandle.open(filename, ios::out | ios::trunc);
    outFileHandle << fixed << setprecision(4);
    for (int i = 0; i < loftSurface.size(); i++)
    {
        for (int j = 0; j < loftSurface[i].size(); j++) {
            for (int k = 0; k < 3; k++) {
                outFileHandle << loftSurface[i][j].data[k] << " ";
            }
            outFileHandle << endl;
        }
        outFileHandle << endl;
    }
    outFileHandle.close();
    return true;
} 

bool displayGNU(string programName, vector <string> dataFiles) {     ofstream outFileHandle;
    outFileHandle.open("gnuScript.plt", ios::out | ios::trunc);
    outFileHandle << "set title '" << programName <<"'"<< endl;
    outFileHandle << "set view equal xyz"<<endl;
    outFileHandle << "set view ,,.3" << endl;
    //outFileHandle << "set nokey" << endl; 
    outFileHandle << "set hidden3d" << endl;     outFileHandle << "splot ";
    for (int i=0; i < dataFiles.size(); i++)
    {
        outFileHandle << "'"<<dataFiles[i]<<"' w l";
        if (i < (dataFiles.size()-1))
            outFileHandle << ",";
    }     outFileHandle <<endl<< "pause -9 \"Hit Enter\" " << endl;
    outFileHandle.close();     system("wgnuplot.exe gnuScript.plt");
    return true;
} 

bool generateSurfaceLoft(Curve c1, Curve c2, int numV, Surface& loftSurface)
{
    if (c1.size() != c2.size())
        return false;

    double  deltaV = 1.0 / (numV - 1);

    Curve c;
    c.resize(c1.size());

    for (double v = 0; v <= (1.0 + _MFR_TOL_); v += deltaV)
    {
        for (int i = 0; i < c1.size(); i++) {
            for (int j = 0; j < 3; j++) {
                c[i].data[j] = c1[i].data[j] * (1 - v) + c2[i].data[j] * v;
            }
        }
        loftSurface.push_back(c);
    }
    return true;
} 

int main(int argc, char** argv)
{
    string programName;
    vector <string> dataFiles;
    programName = argv[0];     
    int index = 0;
    vector <Curve> sections;
    vector <Surface> surfacesPatch;
    sections.resize(10);
    surfacesPatch.resize(9);     
    
    //bottum surface  index = 0
    generateConics(GVector{ 0.0,0.0,0.0 }, 0, 0, 72, sections[index]); 
    generateConics(GVector{ 0.0,0.0,0.0 }, 30, 30, 72, sections[index+1]);  
    generateSurfaceLoft(sections[index], sections[index+1], 10, surfacesPatch[index]);
    dataFiles.push_back("baseSurface.gnu");
    writeGNU(surfacesPatch[index], dataFiles.back());
    index++;     
    
    //chamfer surface index = 1    
    generateConics(GVector{ 0.0,0.0,12.0 }, 40, 40, 72, sections[index+1]); 
    generateSurfaceLoft(sections[index ], sections[index+1], 10, surfacesPatch[index]);
    dataFiles.push_back("chamferSurface.gnu");  
    writeGNU(surfacesPatch[index ], dataFiles.back());
    index++;     
    
    //main surface index = 2    
    generateConics(GVector{ 0.0,0.0,170.0 }, 40, 40, 72, sections[index+1]);
    generateSurfaceLoft(sections[index], sections[index+1], 10, surfacesPatch[index]);
    dataFiles.push_back("mainSurface.gnu");
    writeGNU(surfacesPatch[index], dataFiles.back());
    index++;     
    
    //conic surface index = 3    
    generateConics(GVector{ 0.0,0.0,230.0 }, 20, 20, 72, sections[index + 1]);
    generateSurfaceLoft(sections[index], sections[index + 1], 10, surfacesPatch[index]);
    dataFiles.push_back("conicSurface.gnu");
    writeGNU(surfacesPatch[index], dataFiles.back());
    index++;     
    
    //extend surface index = 4    
    generateConics(GVector{ 0.0,0.0,290.0 }, 20, 20, 72, sections[index + 1]);
    generateSurfaceLoft(sections[index], sections[index + 1], 10, surfacesPatch[index]);
    dataFiles.push_back("extendSurface.gnu");
    writeGNU(surfacesPatch[index], dataFiles.back());
    index++; 

    displayGNU(base_name(programName), dataFiles);
    return 1;
}
*/
