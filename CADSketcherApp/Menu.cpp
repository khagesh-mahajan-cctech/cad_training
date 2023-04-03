#include <iostream>
#include <vector>

#include "Menu.h"
#include "IGeometry.h"
#include "Point.h"
#include "Line.h"
#include "Circle.h"


int Menu::showMenu(std::vector<IGeometry*>& geometry)
{
	unsigned int choice;
	std::cout << "Enter Choice : " << std::endl;
	std::cout << "1. Point Input " << std::endl;
	std::cout << "2. Line Input " << std::endl;
	std::cout << "3. Circle Input " << std::endl;
	std::cout << "4. Display " << std::endl;
	std::cout << "Exit : Enter Anything " << std::endl;

	std::cin >> choice;

	switch (choice)
	{
	case 1:
		{
			IGeometry* pt = new Point();
			pt->input();
			geometry.push_back(pt);
		}
		break;
	case 2:
		{
			IGeometry* line = new Line();
			line->input();
			geometry.push_back(line);
		}
		break;
	case 3:
		{
			IGeometry* circle = new Circle();
			circle->input();
			geometry.push_back(circle);
		}
		break;
	case 4:
		for (auto itr = geometry.begin(); itr != geometry.end(); ++itr)
		{
			(*itr)->display();
		}
		break;
	default :
		return -1;
	}

	return 0;
}
