﻿#include "stdafx.h"
#include "Game.h"
#include <iostream>


Game::Game()
{
	points = 0;
	cash = 0;
	deltaTime = 0.0f;
	this->terrain = new Model("models\\terrain.obj", "models\\textures\\terrain.bmp");
	printLoading("12");
	train = new Train(0, false, &particles, &startTrainHP);
	this->collision = new Collision("models\\terr.txt", train);
	printLoading("87");
	this->cannon = new Cannon();
	printLoading("97");
	this->tutorial = new Tutorial(train);
	this->skybox = new Skybox(60.0f);
	printLoading("99");
	soundEngine = irrklang::createIrrKlangDevice();
	this->loadLevel(currentLevel);

	float width = float(glutGet(GLUT_WINDOW_WIDTH));
	float height = float(glutGet(GLUT_WINDOW_HEIGHT));
	wf = glGenLists(1);
	glNewList(wf, GL_COMPILE);
		glBegin(GL_LINES);
			glVertex2f((width / 2) - 5, (height / 2) + 20);
			glVertex2f((width / 2) + 5, (height / 2) + 20);
			glVertex2f((width / 2) - 10, (height / 2) + 0);
			glVertex2f((width / 2) + 10, (height / 2) + 0);
			glVertex2f((width / 2) - 15, (height / 2) - 20);
			glVertex2f((width / 2) + 15, (height / 2) - 20);
			glVertex2f((width / 2) - 20, (height / 2) - 40);
			glVertex2f((width / 2) + 20, (height / 2) - 40);
		glEnd();
	glEndList();
	bg = glGenLists(1);
	glNewList(bg, GL_COMPILE);
		glBegin(GL_QUADS);
			glVertex2f(0, 0);
			glVertex2f(300, 0);
			glVertex2f(300, 120);
			glVertex2f(0, 120);
		glEnd();
	glEndList();
}

Game::~Game()
{
}

void Game::calculateScene()
{
	train->playerPosX = player.pos.x;
	train->Calculate();

	//Kule
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bool col = collision->isCollision(bullets[i]->getPosition());
		bool collisionWithTrain = collision->isCollisionWithTrain(bullets[i]->getPosition());

		if (collisionWithTrain) // KOLIZJA Z POCIAGIEM
		{
			particles.push_back(new Particle(bullets[i]->getPosition()));
			soundEngine->play2D("sounds/explosion.wav");
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			train->HP -= ((cannon->ballPower * cannon->ballPowerLevel * 1.5f) + rand() % 20);
			if (train->HP < 0) train->HP = 0;
		}
		else if (bullets[i]->getPosition().y < -2.0f) // KOLIZJA Z TERENEM
		{
			particles.push_back(new Particle(bullets[i]->getPosition()));
			soundEngine->play2D("sounds/explosion.wav");
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
		else if (player.pos.distanceTo(bullets[i]->getPosition()) <= 0.2f && bullets[i]->owner == TRAIN) // KOLIZJA Z GRACZEM
		{
			particles.push_back(new Particle(bullets[i]->getPosition()));
			soundEngine->play2D("sounds/explosion.wav");
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			minusHP();
			if (hp < 0) hp = 0;
		}
		else
		{
			bullets[i]->update();
		}
	}

	if (train->bulletReady)
	{
		soundEngine->play2D("sounds/cannon.wav");
		bullets.push_back(
			new Bullet(
				train->startPos,
				train->shootDir,
				Vector3(),
				0.5f,
				TRAIN
			)
		);

		train->bulletReady = false;
	}

	//Particles
	for (size_t i = 0; i < particles.size(); i++)
	{
		if (particles[i]->end)
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
		else
		{
			particles[i]->calculate();
		}
	}

	//Pociag
	if (train->number != -1)
	{
		if (train->number == 0)
		{
			level->curentPoints += level->trainPoint;
			level->curentCash += 50;
		}
		else if (train->number == 1)
		{
			level->curentPoints -= int(level->trainPoint * 0.5f);
			level->curentCash -= 100;
		}
		else if (train->number == 2)
		{
			level->curentPoints += level->trainPoint;
			level->curentCash += 150;
		}
		else if (train->number == 3)
		{
			level->curentPoints += level->trainPoint;
		}

		train->number = -1;
	}

	if (this->cannon->reloading < 0)
	{
		timer = 0;
	}
}

void Game::cannnonUpgradeClicked(int opt)
{
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
	if (currentLevel > 0) {
		if (currentLevel == 5 && level->curentPoints > 0) {
			soundEngine->stopAllSounds();
			return true;
		}

		if (currentLevel == 5)
			return false;

		if (level->getRemainingTime() < 0) {
			soundEngine->stopAllSounds();
			return true;
		}
		else
			return false;
	}
	else if (tutorial->end == true) {
		delete tutorial;
		soundEngine->stopAllSounds();
		return true;
	}
	else
		return false;
}

void Game::loadLevel(int l) {
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glutSetCursor(GLUT_CURSOR_NONE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), .01f, 120.0f);

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

#pragma region Swiatlo_ogolne

	float l0_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float l0_dif[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float l0_spe[] = { 0.5f, 0.5f, 0.5f, 0.2f };
	float l0_pos[] = { 0.0f, 30.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);

#pragma endregion

	if (l > 0) {
		this->level = new Level(l);
		if (l == 5)
			train->isBoss = true;
		else
			train->isBoss = false;

		train->speed = level->trainSpeed;
		train->setDefault(200 * currentLevel / 5);

		this->player.pos.x = level->sX;
		this->player.pos.y = 0.3f;
		this->player.pos.z = level->sZ;

		//Mgla
		float fcolor[] = { 0.875f, 0.957f, 1.0f, 1.0f };
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogfv(GL_FOG_COLOR, fcolor);
		glFogf(GL_FOG_START, 1.0f);
		glFogf(GL_FOG_END, 40.0f + 120.0f * ((5.0f - l) / 5));
		glEnable(GL_FOG);

		windOffset = 0.0f;
		windChange = true;
		posOffset = 0.0f;
		totalLoadingTime = (cannon->fireRate - cannon->fireRateLevel) * 25.0f;
	}
	train->playerPosX = player.pos.x;
	train->playerPosZ = player.pos.z;

	this->player.dir.x = 0.0f;
	this->player.dir.y = 0.0f;
	this->player.dir.z = -1.0f;

	this->player.speed = 0.5f;

	this->player.velRX = 0;
	this->player.velRY = 0;
	this->player.velX = 0;

	this->timer = 0;
	cannon->reloading = 0;
	soundEngine->play2D("sounds/gameMusic.wav", true);
}

void Game::cleanMem(){
	for (size_t i = 0; i < particles.size(); i++)
		delete particles[i];
	particles.clear();

	for (size_t i = 0; i < bullets.size(); i++)
		delete bullets[i];
	bullets.clear();
}

void Game::minusHP(){
	hp -= rand() % (5 - 1 + 1) + 1;
}

void Game::renderTerrain() {
	terrain->show();
	//collision->Render();
}

void Game::renderSkybox() {
	if (currentLevel > 0) glDisable(GL_FOG);
	skybox->show();
	if(currentLevel > 0) glEnable(GL_FOG);
}

void Game::renderCannon() {
	glPushMatrix();
		glTranslatef(player.pos.x, player.pos.y, player.pos.z);
		glRotatef(hAngle - 90, 0, 1, 0);
		glRotatef(vAngle, 0, 0, 1);
		cannon->show();
	glPopMatrix();
}

void Game::renderTrain() {
	glPushMatrix();
		train->show();
	glPopMatrix();
}

void Game::renderBullets() {
	for (size_t i = 0; i < bullets.size(); i++) {
		glPushMatrix();
			bullets[i]->show();
		glPopMatrix();
	}
}

void Game::renderParticles() {
	for (size_t i = 0; i < particles.size(); i++) {
		glPushMatrix();
		particles[i]->show();
		glPopMatrix();
	}
}

void Game::renderHUD() {
	if (currentLevel < 5) {
		printText(20, 20, 10, "Poziom: " + std::to_string(currentLevel), 1, 1, 1);
		printText(20, 40, 10, "Czas: " + std::to_string(level->getRemainingTime()), 1, 1, 1);
		printText(20, 60, 10, "Punkty: " + std::to_string(level->curentPoints) + "/" + std::to_string(level->requiredPoints), 1, 1, 1);
		if (windChange)
			printText(20, 80, 10, "Wiatr: " + std::to_string(int((level->wind + abs(windOffset)) * 10000)) + "m/s", 1, 0.8f, 0.8f);
		else
			printText(20, 80, 10, "Wiatr: " + std::to_string(int((level->wind + abs(windOffset)) * 10000)) + "m/s", 0.8f, 1, 0.8f);
		printText(20, 100, 10, "Pociag: " + std::to_string(int(train->HP)) + "HP", 1, 1, 1);
	}
	else {
		printText(20, 20, 10, "Poziom: " + std::to_string(currentLevel), 1, 1, 1);
		printText(20, 40, 10, "Zdrowie: " + std::to_string(hp) + "%", 1, 1, 1);
		printText(20, 60, 10, "Punkty: " + std::to_string(level->curentPoints) + "/" + std::to_string(level->requiredPoints), 1, 1, 1);
		if(windChange)
			printText(20, 80, 10, "Wiatr: " + std::to_string(int((level->wind + abs(windOffset)) * 10000)) + "m/s +", 1, 0.8f, 0.8f);
		else
			printText(20, 80, 10, "Wiatr: " + std::to_string(int((level->wind + abs(windOffset)) * 10000)) + "m/s -", 0.8f, 1, 0.8f);
		printText(20, 100, 10, "Pociag: " + std::to_string(int(train->HP)) + "HP", 1, 1, 1);
	}

	if (this->cannon->reloading > 0 && timer++ % 30 < 15)
		printText((glutGet(GLUT_WINDOW_WIDTH) / 2.0f) - 100.0f, (glutGet(GLUT_WINDOW_HEIGHT) / 2.0f) + 100.0f, 5, "Ladowanie pocisku...", 0, 0, 1);

	if (currentLevel == 5 && keysTimer > 0) {
		keysTimer--;
		printText((glutGet(GLUT_WINDOW_WIDTH) / 2.0f) - 185.0f, (glutGet(GLUT_WINDOW_HEIGHT) / 2.0f) + 130.0f, 5, "Omijaj pociski za pomoca klawiszy Q E", 0, 0, 1);
	}

	drawHUDelements(wf, bg, cannon->reloading / totalLoadingTime, train->HP/ startTrainHP);
}

void Game::renderTutorial() {
	tutorial->show();
}
