#ifndef _POINT_H
#define _POINT_H

#include "IGeometry.h"

class Point : public IGeometry
{
private:
	double x, y, z;

public:
	Point();
	Point(double x, double y);
	Point(double x, double y, double z);

	void input();
	void display();

	double getX();
	void setX(double x);

	double getY();
	void setY(double y);

	double getZ();
	void setZ(double z);
};

#endif // !_POINT_H

