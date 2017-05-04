#pragma once
class Bullet
{
public:
	Bullet(float, float, float, float, float, float, float, float, float);
	~Bullet();
	struct vec3 {
		float x, y, z;
	};

	struct BulletState {
		vec3 pos;
		vec3 dir;
		float speed;
		float angle;
		float wind;
	};

	BulletState state;
	void show();

private:
	void move();
	float getDistance(vec3, vec3);
	float getYParameter();
	vec3 startPosition;
	float t = 0;
};

