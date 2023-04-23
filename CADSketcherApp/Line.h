#ifndef _LINE_H
#define _LINE_H

#include "IGeometry.h"
#include "Point.h"

class Line : public IGeometry
{
private:
	Point startPoint;
	Point endPoint;
public:
	Line();

	void input();
	void display();

	void generateLine(Point& startPoint, Point& endPoint, unsigned int numU);
};

#endif

