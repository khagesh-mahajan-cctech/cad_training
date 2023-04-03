#ifndef _IGEOMETRY_H
#define _IGEOMETRY_H

#include <string>

class IGeometry
{
private:
	std::string entityName;

public :
	IGeometry(){}
	IGeometry(std::string entityName) : entityName(entityName) { }

	virtual void input() = 0;
	virtual void display() = 0;

	std::string getEntityName()
	{
		return entityName;
	}

	void setEntityName(std::string entityName)
	{
		this->entityName = entityName;
	}
};

#endif


