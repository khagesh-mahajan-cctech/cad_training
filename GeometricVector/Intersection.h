#ifndef _INTERSECTION_H
#define _INTERSECTION_H

#include <iostream>
#include "Point.h"
#include "Line.h"

namespace GeomVector
{
	bool Intersection(const Point2d&, const Point2d&, const Point2d&, const Point2d&);

	bool Intersection(const Point2d&, const Point2d&, const Point2d&, const Point2d&, Point2d&);

	bool Intersection(const Line2d&, const Line2d&, Point2d);
}
#endif // !_INTERSECTION_H

