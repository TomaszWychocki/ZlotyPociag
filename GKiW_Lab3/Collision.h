#pragma once
#include <vector>
#include <iostream>
#include "Train.h"

class Collision
{
	struct vec3 {
		float x, y, z;

		vec3(float nx, float ny, float nz) {
			x = nx;
			y = ny;
			z = nz;
		}

		vec3() {
			x = 0;
			y = 0;
			z = 0;
		}
	};

public:
	Collision(char *, Train *t);
	~Collision();
	bool isCollision(float x, float y, float z);
	bool isCollisionWithTrain(float x, float y, float z);
	void Render();

private:
	std::vector<vec3> positions[9][29];
	int wMax = 8, kMax = 28;
	Train * train;

	vec3 trainMin;
	vec3 trainMax;
};

