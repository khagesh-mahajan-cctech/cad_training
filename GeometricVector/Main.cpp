#include <iostream>
#include "Core/Base/Vector.h"

int main()
{
	GeomVector::Vector<float, 2> vec1(1.0f, 2.0f);
	GeomVector::Vector<float, 2> vec2(3.0f, 4.0f);

	std::cout << crossProduct2D(vec1, vec2) << std::endl;

}