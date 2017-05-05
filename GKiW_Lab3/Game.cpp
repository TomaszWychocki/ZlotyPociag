#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <mmsystem.h>

Game::Game() {
	points = 0;
	cash = 200;

	this->cannon = new Cannon();
	this->loadLevel(currentLevel);
}


Game::~Game() {

}

void Game::showScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		this->player.pos.x, this->player.pos.y, this->player.pos.z,
		this->player.pos.x + this->player.dir.x, this->player.pos.y + this->player.dir.y, this->player.pos.z + this->player.dir.z,
		0.0f, 1.0f, 0.0f
	);

#pragma region Swiatlo_0

	float l0_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float l0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l0_spe[] = { 0.2f, 0.2f, 0.2f, 0.2f };
	float l0_pos[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	float lightDir[3] = { this->player.dir.x, this->player.dir.y, this->player.dir.z };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);

#pragma endregion

#pragma region Szesciany

	float m0_amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m0_spe[] = { 0.2f, 0.2f, 0.2f, 0.2f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m0_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m0_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m0_spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.2f);

	for (int i = -10; i <= 10; i += 2) {
		for (int j = -10; j <= 10; j += 2) {
			glPushMatrix();
				glTranslatef(i, 0.0f, j);
				glutSolidSphere(0.5, 30, 30);
			glPopMatrix();
		}
	}

	//Kule
	for (size_t i = 0; i < bullets.size(); i++) {
		if (bullets[i]->state.pos.y < -0.25f) {
			particles.push_back(new Particle(bullets[i]->state.pos.x, bullets[i]->state.pos.y, bullets[i]->state.pos.z));
			PlaySound("explosion.wav", NULL, SND_ASYNC | SND_FILENAME);
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
		else
			bullets[i]->show();
	}

	//Particles
	for (size_t i = 0; i < particles.size(); i++) {
		if (particles[i]->end) {
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
		else
			particles[i]->show();
	}

	float m1_amb[] = { 0.5f, 1.0f, 0.0f, 1.0f };
	float m1_dif[] = { 0.5f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m1_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m1_dif);
	glPushMatrix();
	glTranslatef(0, -0.5f, 0);
	glScalef(40.0f, 1.0f, 40.0f);
	glutSolidCube(0.5f);
	glPopMatrix();

	drawViewfinder();
#pragma endregion

	if (currentLevel < 5) {
		printText(20, 20, 10, "Poziom: " + std::to_string(currentLevel), 1, 1, 1);
		printText(20, 40, 10, "Czas: " + std::to_string(level->getRemainingTime()), 1, 1, 1);
		printText(20, 60, 10, "Punkty: " + std::to_string(level->curentPoints) + "/" + std::to_string(level->requiredPoints), 1, 1, 1);
		printText(20, 80, 10, "Wiatr: " + std::to_string(int(level->wind * 10000)) + "m/s", 1, 1, 1);
	}
	else {
		printText(20, 20, 10, "Poziom: " + std::to_string(currentLevel), 1, 1, 1);
		printText(20, 40, 10, "Zdrowie: 100%", 1, 1, 1);
		printText(20, 60, 10, "Punkty: " + std::to_string(level->curentPoints) + "/" + std::to_string(level->requiredPoints), 1, 1, 1);
		printText(20, 80, 10, "Wiatr: " + std::to_string(int(level->wind * 10000)) + "m/s", 1, 1, 1);
	}

	if (this->cannon->reloading > 0) {
		if(timer++ % 30 < 15)
			printText(500, 120, 5, "Ladowanie pocisku...", 1, 0, 0);
	}
	else
		timer = 0;
}

void Game::cannnonUpgradeClicked(int opt) {
	message = "";
	switch (opt)
	{
	case 0:
		if (cannon->fireRateLevel < 5) {
			if (cannon->fireRateLevel < currentLevel) {
				if (cannon->fireRatePrices[cannon->fireRateLevel - 1] <= cash) {
					cash -= cannon->fireRatePrices[cannon->fireRateLevel - 1];
					cannon->fireRateLevel++;
				}
				else
					message = "Brak pieniedzy";
			}
			else
				message = "Twoj poziom jest zbyt maly";
		}
		break;
	case 1:
		if (cannon->ballPowerLevel < 5) {
			if (cannon->ballPowerLevel < currentLevel) {
				if (cannon->ballPowerPrices[cannon->ballPowerLevel - 1] <= cash) {
					cash -= cannon->ballPowerPrices[cannon->ballPowerLevel - 1];
					cannon->ballPowerLevel++;
				}
				else
					message = "Brak pieniedzy";
			}
			else
				message = "Twoj poziom jest zbyt maly";
		}
		break;
	case 2:
		if (cannon->ballSpeedLevel < 5) {
			if (cannon->ballSpeedLevel < currentLevel) {
				if (cannon->ballSpeedPrices[cannon->ballSpeedLevel - 1] <= cash) {
					cash -= cannon->ballSpeedPrices[cannon->ballSpeedLevel - 1];
					cannon->ballSpeedLevel++;
				}
				else
					message = "Brak pieniedzy";
			}
			else
				message = "Twoj poziom jest zbyt maly";
		}
		break;
	case 3:
		glutLeaveMainLoop();
		break;
	case 4:
		delete level;
		loadLevel(currentLevel);
		break;
	}
}

bool Game::checkTime(){
	if (currentLevel == 5)
		return false;

	if (level->getRemainingTime() < 0)
		return true;
	else
		return false;
}

void Game::loadLevel(int l) {
	glEnable(GL_DEPTH_TEST);
	glutSetCursor(GLUT_CURSOR_NONE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), .01f, 100.0f);

	// Ustawiamy komponent ambient naszej sceny - wartosc niezalezna od swiatla (warto zresetowac)
	float gl_amb[] = { 0.01f, 0.01f, 0.01f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	glEnable(GL_LIGHTING); // Wlaczenie oswietlenia
	glShadeModel(GL_SMOOTH); // Wybor techniki cieniowania
	glEnable(GL_LIGHT0); // Wlaczenie 0-go zrodla swiatla

	float l1_amb[] = { 0.6f, 0.2f, 0.0f, 1.0f };
	float l1_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l1_spe[] = { 0.2f, 0.2f, 0.2f, 0.2f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, l1_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1_dif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l1_spe);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 3.0f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

	this->level = new Level(l);

	this->player.pos.x = level->sX;
	this->player.pos.y = 0.0f;
	this->player.pos.z = level->sZ;

	this->player.dir.x = 0.0f;
	this->player.dir.y = 0.0f;
	this->player.dir.z = -1.0f;

	this->player.speed = 0.5f;

	this->player.velM = 0;
	this->player.velS = 0;

	this->timer = 0;
	cannon->reloading = 0;
}

void Game::cleanMem(){
	for (size_t i = 0; i < particles.size(); i++)
		delete particles[i];
	particles.clear();

	for (size_t i = 0; i < bullets.size(); i++)
		delete bullets[i];
	bullets.clear();
}
