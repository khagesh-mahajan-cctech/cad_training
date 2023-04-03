#include <iostream>
#include "Point.h"
#include "IGeometry.h"

Point::Point() : x(0.0), y(0.0), IGeometry("Point") { }

Point::Point(double x, double y) : x(x), y(y) { } 

void Point::input()
{
	std::cout << "Enter Point Coordinates (X,Y) : ";
	std::cin >> x >> y;
}

void Point::display()
{
	std::cout << getEntityName() << " :- {X : " << x << " , Y : " << y  << " }" << std::endl;
}
