#pragma once
#include "Train.h"
#include "Point.h"
#include <vector>
#include <iostream>

class Collision
{
public:
	Collision(char *, Train *train);
	~Collision();
	bool isCollision(const Point & point);
	bool isCollisionWithTrain(const Point & point);
	void show();

private:
	std::vector<Point> positions[9][29];
	size_t wMax = 8, kMax = 28;
	Train * train;

	Point trainMin;
	Point trainMax;
};

