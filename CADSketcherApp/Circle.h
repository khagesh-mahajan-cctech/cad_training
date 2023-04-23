#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "IGeometry.h"
#include "Point.h"

class Circle : public IGeometry
{
private:
	double radius;
	Point point;

public:
	Circle();

	double getRadius() { return radius; }
	void setRadius(double radius) { this->radius = radius; }

	void input();
	void display();

	void generateCircle(double radius, Point centerPoint, unsigned int numU);
};

#endif

