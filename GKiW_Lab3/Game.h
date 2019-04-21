#pragma once
#include "Level.h"
#include "Cannon.h"
#include "Bullet.h"
#include "Particle.h"
#include "FunctionsPack.h"
#include "Train.h"
#include "Model.h"
#include "Tutorial.h"
#include "Skybox.h"
#include "Collision.h"
#include "Vector3.h"
#include "Point.h"
#include <vector>
#include <irrKlang.h>

class Game
{
	struct SCameraState
	{
		Point pos;
		Vector3 dir;
		float speed;
		float velRY, velRX;
		float velX;
	};

public:
	Game();
	~Game();
	void calculateScene();
	void cannnonUpgradeClicked(int);
	bool checkTime();
	void loadLevel(int);
	void cleanMem();
	void minusHP();

	void renderTerrain();
	void renderSkybox();
	void renderCannon();
	void renderTrain();
	void renderBullets();
	void renderParticles();
	void renderHUD();
	void renderTutorial();

	SCameraState player;
	Vector3 LightPos;
	bool lightEnabled = true;
	Level *level;
	Cannon *cannon;
	Tutorial *tutorial;
	std::string message = "";
	int currentLevel = 0;
	int points;
	int cash;
	int hp = 100;
	float hAngle;
	float vAngle;
	float windOffset;
	bool windChange;
	float posOffset;
	float deltaTime;

	std::vector <Bullet*> bullets;
	std::vector <Particle*> particles;

private:
	int timer;
	int keysTimer = 300;
	float totalLoadingTime;
	float startTrainHP;
	GLuint wf, bg;
	Model *terrain;
	Train *train;
	irrklang::ISoundEngine* soundEngine;
	Skybox *skybox;
	Collision *collision;
};

