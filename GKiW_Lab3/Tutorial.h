#pragma once
#include "Train.h"
#include "FunctionsPack.h"

class Tutorial
{
	struct vec3 {
		float x, y, z;
	};

	struct SCameraState {
		vec3 pos;
		vec3 dir;
	};

public:
	Tutorial(Train *t);
	~Tutorial();
	void show();
	bool end = false;

private:
	Train *train;
	float timer = 0.0f;
	SCameraState player;
	int frame = 1;
};

