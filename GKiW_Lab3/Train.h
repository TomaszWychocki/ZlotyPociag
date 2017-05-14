#pragma once
#include "Model.h"

class Train
{
public:
	Train(float s, bool isBoss);
	~Train();
	void LoadModels();
	void Render();
	void setDefault();
	float HP;
	float speed;
	bool isBoss;
	int number;

private:
	Model *trains[4]; //Normal, blue, green, gold
	Model *trainCannon;
	void setRandomTrain();
	int currentTrain = 0;
	float timer;
	float posX;
	float posY;
	bool dir = false;
	bool isDead;
};

