#pragma once
class Particle
{
	struct vec3 {
		float x, y, z;
	};

public:
	Particle(float, float, float);
	float randMToN(float, float);
	~Particle();
	void show();
	bool end = false;

private: 
	float Offset = 0;
	vec3 startPos;
	vec3 par[100];
	vec3 color[100];
	vec3 angle;
};

