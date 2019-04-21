#include "stdafx.h"
#include "Point.h"
#include "Vector3.h"


Point::Point()
{
}

Point::Point(float x, float y, float z) :
	x(x), y(y), z(z)
{
}

Point::Point(const Point & point) :
	x(point.x), y(point.y), z(point.z)
{
}

Point::~Point()
{
}

void Point::operator=(const Point & point)
{
	this->x = point.x;
	this->y = point.y;
	this->z = point.z;
}

void Point::move(const Vector3 & vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
}

float Point::distanceTo(const Point & point) const
{
	return sqrtf(
		powf(this->x - point.x, 2) +
		powf(this->y - point.y, 2) +
		powf(this->z - point.z, 2)
	);
}
