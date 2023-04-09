#ifndef _GEOUTILS_H
#define _GEOUTILS_H

#include <iostream>
#include <vector>
#include "Point.h"

namespace GeomVector
{
	double areaTriangle2D(const Point2d& a, const Point2d& b, const Point2d& c);

	int orientation2D(const Point2d& a, const Point2d& b, const Point2d& c);
}

#endif // !_GEOUTILS_H


