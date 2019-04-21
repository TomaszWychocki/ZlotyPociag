#pragma once
#include "Vector3.h"

class Point
{
public:
	float x, y, z;

	Point();
	Point(float x, float y, float z);
	Point(const Point & point);
	~Point();

	void operator=(const Point & point);

	void move(const Vector3 & vec);
	float distanceTo(const Point & point) const;
};

