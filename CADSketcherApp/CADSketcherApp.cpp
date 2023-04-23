// CADSketcherApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "IGeometry.h"
#include "Menu.h"
#include "Point.h"

int main()
{
    std::cout << "Welcome To Sketcher App!\n";

    std::vector<IGeometry*> geometry;
    
    Menu menu;
    unsigned int input{ 0 };

    do {
        input = menu.showMenu(geometry);
    } while (input != -1);
    
}