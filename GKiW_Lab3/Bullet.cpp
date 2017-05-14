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
	//std::cout << state.angle << std::endl;

	float l1_pos[] = { state.pos.x, state.pos.y, state.pos.z, 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, l1_pos);
	glEnable(GL_LIGHT1);
}

Bullet::~Bullet(){
	std::cout << "Delete" << std::endl;
}

void Bullet::show(){
	glPushMatrix();
		glTranslatef(state.pos.x, state.pos.y, state.pos.z);
		glutSolidSphere(0.1, 30, 30);
	glPopMatrix();

	move();
}

void Bullet::move(){
	state.pos.x += state.dir.x * state.speed * 0.7;
	state.pos.y = getYParameter(); // *0.7
	state.pos.z += (state.dir.z * state.speed + (state.wind * t)) * 0.7;
	t += 1;

	if (t > 5)
		glDisable(GL_LIGHT1);
	//std::cout << state.pos.x << " " << state.pos.y << " " << state.pos.z << " " << std::endl;
}

float Bullet::getDistance(vec3 a, vec3 b) {
	return sqrt(pow(b.x - a.x, 2) - pow(b.z - a.z, 2));
}

float Bullet::getYParameter() {
	return ((tan(state.angle)*t) - ((9.8*pow(t, 2)) / (2 * pow(state.speed*80, 2)*pow(cos(state.angle),2)))) + startPosition.y + state.dir.y;
}
