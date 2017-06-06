#pragma once
#include "Model.h"
#include <irrKlang.h>
#include <vector>
#include "Particle.h" 

class Train
{
	struct vec3 {
		float x, y, z;
	};

public:
	Train(float s, bool isBoss, std::vector<Particle*> *v, float *h);
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
	float posX;
	bool dir = false;
	vec3 shootDir;
	vec3 startPos;

private:
	Model *trains[4]; //Normal, blue, green, gold
	Model *trainCannon;
	irrklang::ISoundEngine* se;
	void setRandomTrain();
	int currentTrain = 0;
	float timer;
	float posY;
	bool isDead;
	int HPdelta = 0;
	float a = 0.0;
	float *startHP;
	std::vector<Particle*> *particleVector;
};

