#ifndef _LINE_H
#define _LINE_H

#include "IGeometry.h"
class Line : public IGeometry
{
	void input();
	void display();

	void generateLine();
};

#endif

