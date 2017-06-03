#include "Level.h"
#include "Cannon.h"
#include "Bullet.h"
#include "Particle.h"
#include <vector>
#include "FunctionsPack.h"
#include "Train.h"
#include "Model.h"
#include <irrKlang.h>
#include "Tutorial.h"
#include "Skybox.h"

class Game
{
	struct vec3 {
		float x, y, z;
	};

	struct SCameraState {
		vec3 pos;
		vec3 dir;
		float speed;
		float velRY, velRX;
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
	vec3 LightPos;
	bool lightEnabled = true;
	Level *level;
	Cannon *cannon;
	Tutorial *tutorial;
	std::string message = "";
	int currentLevel = 5;
	int points;
	int cash;
	int hp = 100;
	float hAngle;
	float vAngle;
	float windOffset;
	bool windChange;

	std::vector < Bullet* > bullets;
	std::vector < Particle* > particles;

private:
	int timer;
	Model *terrain;
	Train *train;
	irrklang::ISoundEngine* se;
	Skybox *skybox;
};

