#pragma once
#include "Model.h"
#include <irrKlang.h>

class Train
{
	struct vec3 {
		float x, y, z;
	};

public:
	Train(float s, bool isBoss);
	~Train();
	void LoadModels();
	void Calculate();
	void Render();
	void setDefault(int);
	void showTrainByNumber(int);
	float HP;
	float speed;
	bool isBoss;
	bool bulletReady;
	int number;
	float playerPosX;
	float playerPosZ;
	vec3 shootDir;
	vec3 startPos;

private:
	Model *trains[4]; //Normal, blue, green, gold
	Model *trainCannon;
	irrklang::ISoundEngine* se;
	void setRandomTrain();
	int currentTrain = 0;
	float timer;
	float posX;
	float posY;
	bool dir = false;
	bool isDead;
	int HPdelta = 0;
	float a = 0.0;
};

