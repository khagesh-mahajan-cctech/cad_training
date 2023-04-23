#include <iostream>

#include "Line.h"

Line::Line() : IGeometry("Line") {}

void Line::input()
{
	std::cout << "Enter Start Point Of Line " << std::endl;
	startPoint.input();

	std::cout << "Enter End Point Of Line " << std::endl;
	endPoint.input();

}

void Line::display()
{
	std::cout << getEntityName() << ":-  StartPoint :- { X : " << startPoint.getX() << ", Y : " << startPoint.getY()
		<< " }, EndPoint :- { X : " << endPoint.getX() << ", Y : " << endPoint.getY() << " }" 
		<< std::endl << std::endl;
}

void Line::generateLine(Point& startPoint, Point& endPoint, unsigned int numU)
{
	double deltaX = (endPoint.getX() - startPoint.getX()) / numU;
	double deltaY = (endPoint.getY() - startPoint.getY()) / numU;
	double deltaZ = (endPoint.getZ() - startPoint.getZ()) / numU;

	for (size_t u{ 0 }; u < numU; ++u)
	{
		double x = startPoint.getX() * (1 - deltaX) + deltaX * u;
		double y = startPoint.getY() * (1 - deltaY) + deltaY * u;
		double z = startPoint.getZ() * (1 - deltaZ) + deltaZ * u;
	}
}
