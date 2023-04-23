#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include "Circle.h"

Circle::Circle() : radius(0.0), IGeometry("Circle") {}

void Circle::input()
{
	double radius{ 0.0 };

	std::cout << "Enter Radius of circle : " << std::endl;
	std::cin >> radius;
	setRadius(radius);

	std::cout << "Enter Center Point Of Circle!" << std::endl;
	point.input();
}

void Circle::display()
{
	std::cout << getEntityName() << ":- { Radius : " << getRadius() 
		<< ", CenterPoint :- " << " X : " << point.getX() << ", Y : " << point.getY() << " }" 
		<< std::endl << std::endl;
}

void Circle::generateCircle(double radius, Point centerPoint, unsigned int numU)
{
	double theta = (2 * M_PI) / numU;

	for (double u = 0; u < 2 * M_PI; u += theta)
	{
		(centerPoint.getX() + radius) * cos(u);
		(centerPoint.getY() + radius) * cos(u);
		(centerPoint.getZ() + radius) * cos(u);
	}
}
