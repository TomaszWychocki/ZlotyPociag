#include "stdafx.h"
#include "Bullet.h"
#include "Vector3.h"
#include "Point.h"
#include <iostream>


Bullet::Bullet(const Point & pos, const Vector3 & dir, const Vector3 & wind, float speed, bulletOwner owner) :
	gravity(0.0f, -0.05f, 0.0f)
{
	this->position = pos;
	this->velocity = dir;
	this->wind = wind;
	this->speed = speed;
	this->owner = owner;

	this->velocity.normalize();
	this->velocity.mult(this->speed);

	this->mass = 20.0f;

	//float l1_pos[] = { state.pos.x, state.pos.y, state.pos.z, 1.0f };
	//glLightfv(GL_LIGHT1, GL_POSITION, l1_pos);
	//glEnable(GL_LIGHT1);
}

Bullet::~Bullet()
{
}

void Bullet::show()
{
	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glutSolidSphere(0.1, 30, 30);
	glPopMatrix();
}

void Bullet::update()
{
	this->acceleration.mult(0);
	this->acceleration.add(this->wind);
	this->acceleration.add(this->gravity);

	this->acceleration.div(this->mass);

	this->velocity.add(this->acceleration);
	this->position.move(this->velocity);


	//t = t + 0.3f + (0.06f * state.speed);
	//if (t > 5)
	//	glDisable(GL_LIGHT1);
	//std::cout << state.pos.x << " " << state.pos.y << " " << state.pos.z << " " << std::endl;
}

Point & Bullet::getPosition()
{
	return this->position;
}
