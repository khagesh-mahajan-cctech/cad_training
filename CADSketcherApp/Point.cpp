#include <iostream>
#include "Point.h"
#include "IGeometry.h"

Point::Point() : x(0.0), y(0.0), z(0.0), IGeometry("Point") { }

Point::Point(double x, double y) : x(x), y(y) { } 

Point::Point(double x, double y, double z) : x(x), y(y), z(z) { }

void Point::input()
{
	std::cout << "Enter Point Coordinates (X,Y) : ";
	std::cin >> x >> y;
}

void Point::display()
{
	std::cout << getEntityName() << " :- {X : " << x << " , Y : " << y  << " }" 
		<< std::endl << std::endl;
}

double Point::getX() { return x; }

void Point::setX(double x) { this->x = x; }

double Point::getY() { return y; }

void Point::setY(double y) { this->y = y; }

double Point::getZ() { return y; }

void Point::setZ(double z) { this->z = z; }
