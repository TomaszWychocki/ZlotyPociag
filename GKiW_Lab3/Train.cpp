#include "stdafx.h"
#include "Train.h"
#include <iostream>


Train::Train(float s, bool isBoss, std::vector<Particle*> *v, float *h) {
	this->speed = s;
	this->isBoss = isBoss;
	isDead = false;
	startHP = h;
	particleVector = v;
	se = irrklang::createIrrKlangDevice();
	LoadModels();
	setRandomTrain();
}


Train::~Train() {

}

void Train::LoadModels() {
	trains[0] = new Model("models\\Train.obj", "models\\textures\\Train.bmp");
	printLoading("25");
	trains[1]= new Model("models\\Train_blue.obj", "models\\textures\\Train_blue.bmp");
	printLoading("37");
	trains[2] = new Model("models\\Train_green.obj", "models\\textures\\Train_green.bmp");
	printLoading("50");
	trains[3] = new Model("models\\Train_gold.obj", "models\\textures\\Train_gold.bmp");
	printLoading("62");
	trainCannon = new Model("models\\Train_cannon.obj", "models\\textures\\Train_cannon.bmp");
	printLoading("75");
}

void Train::Calculate() {
	if (HP <= 0 && !isDead) {
		se->play2D("sounds/locomotive.wav");
		for (int i = 0; i <= 8; i++) {
			se->play2D("sounds/explosion.wav");
			if (dir)
				particleVector->push_back(new Particle((posX - 0.26097f) + (float)i / 2, 0.3f, 0.0f));
			else
				particleVector->push_back(new Particle((posX + 0.26097f) - (float)i / 2, 0.3f, 0.0f));
		}
		number = currentTrain;
		isDead = true;
	}

	if (isDead) {
		posY -= 0.05f;
		if (posY <= -2.0f)
			setRandomTrain();
	}

	if (dir) {
		if (timer <= -120 && HP > 0)
			setRandomTrain();
	}
	else {
		if (timer >= 120 && HP > 0)
			setRandomTrain();
	}

	if (currentTrain == 1) {
		if (dir)
			timer -= speed * 1.5f;
		else
			timer += speed * 1.5f;
	}
	else {
		if (dir)
			timer -= speed;
		else
			timer += speed;
	}
	posX = (timer / 10);


	if (isBoss) {
			if (dir)
				a = atan2f(playerPosX - (posX + 1.16582f), playerPosZ);
			else
				a = atan2f(playerPosX - (posX - 1.16582f), playerPosZ);
			a = a * 180 / 3.1415;

			if (abs(timer - 20) <= 0.5f || abs(timer - 0) <= 0.5f) {
				if (dir) {
					shootDir.x = playerPosX - (posX + 1.16582f);
					startPos.x = posX + 1.16582f;
				}
				else {
					shootDir.x = playerPosX - (posX - 1.16582f);
					startPos.x = posX - 1.16582f;
				}
				shootDir.y = -0.25f;
				startPos.y = 0.5f;
				shootDir.z = playerPosZ;
				startPos.z = 0;
				float l = sqrt(shootDir.x*shootDir.x + shootDir.y*shootDir.y + shootDir.z*shootDir.z);
				shootDir.x /= l;
				shootDir.y /= l;
				shootDir.z /= l;
				bulletReady = true;
			}

	}
}

void Train::Render() {
	glTranslatef(posX, posY, 0.0f);
	if (isBoss) {
		glPushMatrix();
			if (dir)
				glTranslatef(1.16582f, 0.25899f, 0.0f);
			else
				glTranslatef(-1.16582f, 0.25899f, 0.0f);
			glRotatef(a, 0, 1, 0);
			trainCannon->Render();
		glPopMatrix();
	}

	if (!dir)
		glRotatef(180.0f, 0, 1, 0);
	trains[currentTrain]->Render();
}

void Train::setDefault(int hpd) {
	dir = false;
	isDead = false;
	HPdelta = hpd;
	if (isBoss) {
		HP = 1000;
	}
	setRandomTrain();
}

void Train::showTrainByNumber(int n) {
	timer++;
	glPushMatrix();
		glTranslatef(-1.0f, 0.1f, 0.0f);
		if (n == 3) {
			glPushMatrix();
				glTranslatef(1.16582f, 0.25899f, 0.0f);
				glRotatef(sin(timer/70)*60.0f, 0, 1, 0);
				trainCannon->Render();
			glPopMatrix();
		}
		trains[n]->Render();
	glPopMatrix();
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
	posY = 0.1f;
	dir = !dir;
	if (!isBoss) {
		HP = HPdelta + (rand() % 51);
	}
	*startHP = HP;
	isDead = false;
	bulletReady = false;

	if (dir)
		timer = 70;
	else
		timer = -70;
}
