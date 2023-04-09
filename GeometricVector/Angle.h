#ifndef _ANGLE_H
#define _ANGLE_H

#include <iostream>
#include "Line.h"
#include "Plane.h"

namespace GeomVector
{
	float AngleLine2d(const Line2d&, const Line2d&);

	float AngleLine3d(const Line3d&, const Line3d&);

	float AngleLinePlane(const Line3d&, const Planef&);

	float AnglePlanes(const Planef&, const Planef&);
}

#endif // !_ANGLE_H


