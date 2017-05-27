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
	state.speed = speed;

	if (angle < 900.0f) {
		state.angle = 25.0f * (angle / 90);
		state.angle *= 3.1415 / 180;
		state.wind = wind * 0.8f;
		//std::cout << state.angle << std::endl;
	}
	else
		state.angle = angle;

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
		if (state.angle < 900.0f)
			glutSolidSphere(0.1, 30, 30);
		else
			glutSolidSphere(0.03, 30, 30);
	glPopMatrix();

	move();
}

void Bullet::move(){
	if (state.angle < 900.0f) {
		state.pos.x += (state.dir.x * (state.speed / 12) + (state.wind * t)) * 0.7;
		state.pos.y = getYParameter();
		state.pos.z += state.dir.z * (state.speed / 12) * 0.7;
	}
	else {
		state.pos.x += state.dir.x * 0.58f;
		state.pos.y += state.dir.y * 0.58f;
		state.pos.z += state.dir.z * 0.58f;
	}


	t = t + 0.3f + (0.06f * state.speed);
	//t += 1;
	if (t > 5)
		glDisable(GL_LIGHT1);
	//std::cout << state.pos.x << " " << state.pos.y << " " << state.pos.z << " " << std::endl;
}

float Bullet::getYParameter() {
	return ((tan(state.angle)*t) - ((9.8*pow(t, 2)) / (2 * pow(0.58f * 80, 2)*pow(cos(state.angle), 2)))) + startPosition.y;
}
