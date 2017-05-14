#include "stdafx.h"
#include "Train.h"
#include <iostream>


Train::Train(float s, bool isBoss) {
	this->speed = s;
	this->isBoss = isBoss;
	isDead = false;
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
		number = currentTrain;
		isDead = true;
	}

	if (isDead) {
		posY -= 0.05f;
		if (posY <= -2.0f)
			setRandomTrain();
	}

	if (dir) {
		if (timer <= -390 && HP > 0)
			setRandomTrain();
	}
	else {
		if (timer >= 400 && HP > 0)
			setRandomTrain();
	}

	if (dir)
		timer -= speed;
	else
		timer += speed;
	std::cout << timer << std::endl;
	posX = (timer / 10);

	glScalef(0.35f, 0.35f, 0.35f);
	glTranslatef(posX, posY, 0.0f);
	if (!dir)
		glRotatef(180.0f, 0, 1, 0);
	trains[currentTrain]->Render();
}

void Train::setDefault() {
	dir = false;
	isDead = false;
	if (isBoss) HP = 500;	
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
	posY = 0.4f;
	dir = !dir;
	if (!isBoss) HP = 100;
	isDead = false;

	if (dir)
		timer = 230;
	else
		timer = -240;
}
