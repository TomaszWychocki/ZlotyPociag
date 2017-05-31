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
	void Render();
	void move();
	static float getDistance(float ax, float ay, float az, float bx, float by, float bz) {
		return sqrt(pow(bx - ax, 2) + pow(by - ay, 2) + pow(bz - az, 2));
	}

private:
	float getYParameter();
	vec3 startPosition;
	float t = 0;
};

