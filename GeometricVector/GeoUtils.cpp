#include <iostream>
#include <math.h>
#include <algorithm>

#include "GeoUtils.h"
#include "Core.h"
#include "Point.h"

using namespace GeomVector;

double GeomVector::areaTriangle2D(const Point2d& a, const Point2d& b, const Point2d& c)
{
	auto AB = b - a;
	auto AC = c - a;

	// This will give area of parallelogram
	float area = GeomVector::crossProduct2D(AB, AC);

	return area / 2;
}

int GeomVector::orientation2D(const Point2d& a, const Point2d& b, const Point2d& c)
{
	double area = areaTriangle2D(a, b, c);

	if (area > 0 && area < TOLERANCE)
		area = 0;
	if (area < 0 && area > TOLERANCE)
		area = 0;

	GeomVector::vector2f ab = b - a;
	GeomVector::vector2f ac = c - a;

	if (area > 0)
		return int (RELATIVE_POSITION::LEFT);

	if (area < 0)
		return int (RELATIVE_POSITION::RIGHT);

	if (ab[X] * ac[X] < 0 || ab[Y] * ac[Y] < 0)
		return int (RELATIVE_POSITION::BEHIND);

	if (ab.magnitude() < ac.magnitude())
		return int (RELATIVE_POSITION::BEYOND);
	if (a == c)
		return int (RELATIVE_POSITION::ORIGIN);
	
	if (a == b)
		return int (RELATIVE_POSITION::DESTINATION);

	return int (RELATIVE_POSITION::BETWEEN);
}