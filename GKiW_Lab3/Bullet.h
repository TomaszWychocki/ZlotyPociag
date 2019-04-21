#pragma once
#include "Vector3.h"
#include "Point.h"


enum bulletOwner
{
	TRAIN,
	PLAYER
};

class Bullet
{
public:
	bulletOwner owner;

	Bullet(const Point & pos, const Vector3 & dir, const Vector3 & wind, float speed, bulletOwner owner);
	~Bullet();

	void show();
	void update();
	Point & getPosition();

private:
	float speed;
	float mass;
	Vector3 wind;
	Vector3 gravity;
	Vector3 velocity;
	Vector3 acceleration;
	Point position;
};

