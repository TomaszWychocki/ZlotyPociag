#pragma once
#include "Vector3.h"
#include "Point.h"


class Particle
{
public:
	Particle(const Point & point);
	float randMToN(float, float);
	~Particle();
	void calculate();
	void show();
	bool end = false;

private: 
	float Offset = 0;
	Point startPos;
	Vector3 par[100];
	Vector3 color[100];
	Vector3 angle;
};

