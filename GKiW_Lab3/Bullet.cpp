#include "stdafx.h"
#include "Bullet.h"
#include <iostream>

Bullet::Bullet(float Sx, float Sy, float Sz, float Dx, float Dy, float Dz, float speed, float angle, float wind) {
	state.pos.x = Sx;
	state.pos.y = Sy;
	state.pos.z = Sz;
	state.dir.x = Dx;
	state.dir.y = Dy;
	state.dir.z = Dz;
	startPosition.x = Sx;
	startPosition.y = Sy;
	startPosition.z = Sz;

	state.angle = 25.0f * (angle/90);
	state.angle *= 3.1415 / 180;
	state.speed = speed / 12.0f;
	state.wind = wind;
	std::cout << state.angle << std::endl;
}

Bullet::~Bullet(){
	std::cout << "Delete" << std::endl;
}

void Bullet::show(){
	glPushMatrix();
		glTranslatef(state.pos.x, state.pos.y, state.pos.z);
		glutSolidSphere(0.3, 30, 30);
	glPopMatrix();

	move();
}

void Bullet::move(){
	state.pos.x += state.dir.x * state.speed;
	state.pos.y = getYParameter();
	state.pos.z += state.dir.z * state.speed + (state.wind * t);
	t += 1;
	//std::cout << state.pos.x << " " << state.pos.y << " " << state.pos.z << " " << std::endl;
}

float Bullet::getDistance(vec3 a, vec3 b) {
	return sqrt(pow(b.x - a.x, 2) - pow(b.z - a.z, 2));
}

float Bullet::getYParameter() {
	float dist = t;
	//std::cout << dist << std::endl;
	return ((tan(state.angle)*dist) - ((9.8*pow(dist, 2)) / (2 * pow(state.speed*80, 2)*pow(cos(state.angle),2)))) + startPosition.y;
}
