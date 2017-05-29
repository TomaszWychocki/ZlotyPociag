#include "stdafx.h"
#include "Train.h"
#include <iostream>


Train::Train(float s, bool isBoss) {
	this->speed = s;
	this->isBoss = isBoss;
	isDead = false;
	se = irrklang::createIrrKlangDevice();
	LoadModels();
	setRandomTrain();
}


Train::~Train() {

}

void Train::LoadModels() {
	trains[0] = new Model("Train.3ds");
	trains[1]= new Model("Train_blue.3ds");
	trains[2] = new Model("Train_green.3ds");
	trains[3] = new Model("Train_gold.3ds");
	trainCannon = new Model("Train_cannon.3ds");
}

void Train::Render() {
	if (HP <= 0 && !isDead) {
		se->play2D("sounds/locomotive.wav");
		number = currentTrain;
		isDead = true;
	}

	if (isDead) {
		posY -= 0.05f;
		if (posY <= -2.0f)
			setRandomTrain();
	}

	if (dir) {
		if (timer <= -160 && HP > 0)
			setRandomTrain();
	}
	else {
		if (timer >= 160 && HP > 0)
			setRandomTrain();
	}

	if (dir)
		timer -= speed;
	else
		timer += speed;
	posX = (timer / 10);
	//std::cout << timer << std::endl;

	glTranslatef(posX, posY, 0.0f);
	if (isBoss) {
		glPushMatrix();
			float a;
			if (dir) {
				glTranslatef(3.23f, 1.1f, 0.0f);
				a = atan2f(playerPosX - (posX + 3.23f), playerPosZ);
			}
			else {
				glTranslatef(-3.23f, 1.1f, 0.0f);
				a = atan2f(playerPosX - (posX - 3.23f), playerPosZ);
			}
			a = a * 180 / 3.1415;
			glRotatef(a, 0, 1, 0);
			trainCannon->Render();

			if (abs(timer - 20) <= 0.5f || abs(timer - 0) <= 0.5f) {
				if (dir) {
					shootDir.x = playerPosX - (posX + 3.23f);
					startPos.x = posX + 3.23f;
				}
				else {
					shootDir.x = playerPosX - (posX - 3.23f);
					startPos.x = posX - 3.23f;
				}
				shootDir.y = -0.37f;
				startPos.y = 0.7f;
				shootDir.z = playerPosZ;
				startPos.z = 0;
				float l = sqrt(shootDir.x*shootDir.x + shootDir.y*shootDir.y + shootDir.z*shootDir.z);
				shootDir.x /= l;
				shootDir.y /= l;
				shootDir.z /= l;
				bulletReady = true;
			}
		glPopMatrix();
	}
	if (!dir)
		glRotatef(180.0f, 0, 1, 0);
	trains[currentTrain]->Render();
}

void Train::setDefault() {
	dir = false;
	isDead = false;
	if (isBoss) HP = 1000;	
	setRandomTrain();
}

void Train::setRandomTrain() {
	int r = rand() % 20;
	if (r <= 15)
		currentTrain = 0;
	if(r == 16 || r == 17)
		currentTrain = 1;
	if (r == 18 || r == 19)
		currentTrain = 2;

	if (isBoss) currentTrain = 3;

	posX = 0;
	posY = -0.43f;
	dir = !dir;
	if (!isBoss) HP = 100;
	isDead = false;
	bulletReady = false;

	if (dir)
		timer = 70;
	else
		timer = -60;
}
