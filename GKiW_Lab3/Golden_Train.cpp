#include "stdafx.h"
#include "HighScores.h"
#include "Game.h"
#include "MainMenu.h"
#include "Bullet.h"
#include "CannonUpgradeMenu.h"
#include "Golden_Train.h"
#include "FunctionsPack.h"
#include "Vector3.h"
#include <iostream>
#include <string>
#include <time.h>
#include <irrKlang.h>

//int w = 1366;
//int h = 768;
int w = 0;
int h = 0;

void GetRes(int &hor, int& vert)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	hor = desktop.right;
	vert = desktop.bottom;
}

int main(int argc, char* argv[])
{
	GetRes(w, h);

	glutInit(&argc, argv);

	srand(time(NULL) ^ clock());

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Zloty pociag");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutSpecialFunc(OnSpecialKeyPress);
	glutSpecialUpFunc(OnSpecialKeyUp);
	glutPassiveMotionFunc(OnMove);
	glutMouseFunc(onMouseButton);
	glutTimerFunc(17, OnTimer, 0);

	glutFullScreen();
	soundEngine = createIrrKlangDevice();
	hs = new HighScores();
	m_menu = new MainMenu();

	glutMainLoop();

	return 0;
}

bool keystate[256];
bool keystate_special[256];

void OnKeyPress(unsigned char key, int x, int y)
{
	if (!keystate[key])
	{
		OnKeyDown(key, x, y);
	}

	keystate[key] = true;
}

void OnSpecialKeyPress(int key, int x, int y)
{
	if (!keystate_special[key])
	{
		OnSpecialKeyDown(key, x, y);
	}

	keystate_special[key] = true;
}

void OnKeyDown(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		glutLeaveMainLoop();
	}
}

void OnSpecialKeyDown(int key, int x, int y)
{
}

void OnKeyUp(unsigned char key, int x, int y)
{
	keystate[key] = false;
}

void OnSpecialKeyUp(int key, int x, int y)
{
	keystate_special[key] = false;
}

void OnMove(int x, int y)
{
	if (CurrentState == PLAY) 
	{
		mouseX = x;
		mouseY = y;
	}
}

void onMouseButton(int button, int state, int x, int y)
{
	if (CurrentState == MAIN_MENU)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			switch(m_menu->checkItems(x, y))
			{
			case 0:
				CurrentState = LOADING_SCREEN;
				glutSetCursor(GLUT_CURSOR_NONE);
				horizontalAngle = 160.0f;
				verticalAngle = 0;
				delete m_menu;
				break;
			case 1:
				CurrentState = HIGH_SCORES_SCREEN;
				break;
			case 2:
				glutLeaveMainLoop();
				break;
			}
		}
	}
	else if (CurrentState == HIGH_SCORES_SCREEN)
	{
		if (hs->checkItems(x, y) == 1)
			CurrentState = MAIN_MENU;
	}

	if (CurrentState == CANNON_UPGRADE)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			int o = cannonMenu->checkItems(x, y);

			if (o >= 0)
			{
				game->cannnonUpgradeClicked(o);
				if (o == 4)
				{
					delete cannonMenu;
					glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
					horizontalAngle = 160.0f;
					verticalAngle = 0;
					CurrentState = PLAY;
				}
			}
		}
	}
	else if (CurrentState == PLAY && game->currentLevel > 0)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (game->cannon->reloading == 0)
			{
				soundEngine->play2D("sounds/cannon.wav");
				game->cannon->reloading = (game->cannon->fireRate - game->cannon->fireRateLevel) * 25;
				game->bullets.push_back(
					new Bullet(
						game->player.pos,
						game->player.dir,
						Vector3(),
						float(game->cannon->ballSpeedFactor * game->cannon->ballSpeedLevel),
						PLAYER
					)
				);
			}
		}
	}
	else if (CurrentState == PLAY && game->currentLevel == 0)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			game->tutorial->end = true;
		}
	}
}

void OnTimer(int id)
{

	glutTimerFunc(17, OnTimer, 0);

	lastTm = Tm;
	Tm = float(glutGet(GLUT_ELAPSED_TIME)); // Ile milisekund uplynelo od momentu uruchomienia programu?

	if (game != nullptr)
	{
		game->deltaTime = (Tm - lastTm) / 1000;
	}

	if (CurrentState == PLAY && game->currentLevel > 0)
	{
		//Ruch kamery
		float dx = 0.008f * float(glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX);
		float dy = 0.008f  * float(glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY);

		if (dx != 0 || dy != 0)
		{
			game->player.velRX += dx;
			game->player.velRY += dy;
		}

		horizontalAngle += game->player.velRX;
		verticalAngle += game->player.velRY;
		game->player.velRX *= 0.9f;
		game->player.velRY *= 0.9f;

		if (game->currentLevel == 5)
		{
			game->player.velX *= 0.7f;
			game->player.pos.x += game->player.velX;

			if (game->player.pos.x < -3.75f)
			{
				game->player.pos.x = -3.75f;
			}

			if (game->player.pos.x > 4.0f)
			{
				game->player.pos.x = 4.0f;
			}
		}

		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);

		if (keystate['w'])
		{
			game->player.velRY += 0.07f;
		}
		if (keystate['s'])
		{
			game->player.velRY -= 0.07f;
		}
		if (keystate['a'])
		{
			game->player.velRX += 0.07f;
		}
		if (keystate['d'])
		{
			game->player.velRX -= 0.07f;
		}
		if (keystate['q'] && game->currentLevel == 5)
		{
			game->player.velX -= 0.01f;
		}
		if (keystate['e'] && game->currentLevel == 5)
		{
			game->player.velX += 0.01f;
		}

		if (verticalAngle > 90) verticalAngle = 90;
		if (verticalAngle < 0) verticalAngle = 0;

		game->hAngle = horizontalAngle;
		game->vAngle = verticalAngle;

		game->player.dir.x = cos(verticalAngle*3.14f / 180.0f) * sin(horizontalAngle*3.14f / 180.0f);
		game->player.dir.y = sin(verticalAngle*3.14f / 180.0f);
		game->player.dir.z = cos(verticalAngle*3.14f / 180.0f) * cos(horizontalAngle*3.14f / 180.0f);

		//std::cout << horizontalAngle << " " << verticalAngle << std::endl;

		if (game->cannon->reloading == 0 && keystate[' '])
		{
			soundEngine->play2D("sounds/cannon.wav");
			game->cannon->reloading = (game->cannon->fireRate - game->cannon->fireRateLevel) * 25;
			game->bullets.push_back(
				new Bullet(
					game->player.pos,
					game->player.dir,
					Vector3(),
					float(game->cannon->ballSpeedFactor * game->cannon->ballSpeedLevel),
					PLAYER
				)
			);
		}

		// Znalezienie kierunku prostopadlego
		Vector3 per;
		per.x = -game->player.dir.z;
		per.z = game->player.dir.x;

		if (game->cannon->reloading > 0)
		{
			game->cannon->reloading--;
		}

		if ((int)Tm % 40 < 10)
		{
			float last = game->windOffset;

			if (rand() % 10 >= 5)
			{
				game->windOffset += 0.0001f;
				game->windChange = true;
			}
			else
			{
				game->windOffset -= 0.0001f;
				game->windChange = false;
			}

			if (abs(game->windOffset * 10000) > game->currentLevel * 2)
			{
				game->windOffset = last;
			}
		}
	}

	if (CurrentState == POST_LEVEL_SCREEN)
	{
		if (wait > 0) wait--;
	}

	if (CurrentState == PLAY)
	{
		if (game->checkTime())
		{
			CurrentState = POST_LEVEL_SCREEN;
			glDisable(GL_FOG);
			glDisable(GL_TEXTURE_2D);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			game->cleanMem();
			if (game->currentLevel > 0)
			{
				game->cash += game->level->curentCash;
				game->cash += (int)(game->level->curentPoints * 0.6);

				if (game->level->curentPoints >= game->level->requiredPoints)
				{
					game->points += game->level->curentPoints;
					game->currentLevel++;
				}
			}

			wait = 200;
		}
		else if (game->hp <= 0)
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			wait = 200;
			CurrentState = POST_LEVEL_SCREEN;
			glDisable(GL_FOG);
			game->cleanMem();
		}
		else
		{
			game->calculateScene();
		}
	}
	else if (CurrentState == POST_LEVEL_SCREEN)
	{
		if (wait == 0)
		{
			if (game->currentLevel == 0)
			{
				game->currentLevel = 1;
				game->loadLevel(game->currentLevel);
				CurrentState = PLAY;
			}
			else if (game->currentLevel > 5 || game->hp <= 0)
			{
				glutLeaveMainLoop();
			}
			else
			{
				cannonMenu = new CannonUpgradeMenu(game);
				CurrentState = CANNON_UPGRADE;
			}
		}
	}
	else if (CurrentState == LOADING_SCREEN)
	{
		printLoading("0");
		game = new Game();
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		CurrentState = PLAY;
	}
}

void OnRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(game != nullptr)
		printText(20, 300, 10, "DELTA_TIME: " + std::to_string(game->deltaTime), 1, 1, 1);

	if (CurrentState == MAIN_MENU)
	{
		m_menu->show();
	}
	else if (CurrentState == HIGH_SCORES_SCREEN)
	{
		hs->show();
	}
	else if (CurrentState == PLAY && game->currentLevel > 0)
	{
		gluLookAt(
			game->player.pos.x, game->player.pos.y, game->player.pos.z,
			game->player.pos.x + game->player.dir.x, game->player.pos.y + game->player.dir.y, game->player.pos.z + game->player.dir.z,
			0.0f, 1.0f, 0.0f
		);

		game->renderTerrain();
		game->renderSkybox();
		game->renderCannon();
		game->renderTrain();
		game->renderBullets();
		game->renderParticles();
		game->renderHUD();
	}
	else if (CurrentState == PLAY && game->currentLevel == 0)
	{
		game->renderTutorial();
		game->renderTerrain();
		game->renderSkybox();
	}
	else if (CurrentState == CANNON_UPGRADE)
	{
		cannonMenu->show();
	}
	else if (CurrentState == POST_LEVEL_SCREEN)
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);

		if (game->currentLevel == 0)
		{
			printText(20.0f, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f, 10, "Poziom 1", 1, 1, 1);
		}
		else if (game->currentLevel > 5)
		{
			printText(20.0f, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f, 10, "Wygrales! Twoje punkty: " + std::to_string(game->points), 1, 1, 1);
			hs->saveScore(game->points);
		}
		else if (game->level->curentPoints >= game->level->requiredPoints)
		{
			printText(20.0f, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f, 10, "Przeszedles do poziomu " + std::to_string(game->currentLevel), 1, 1, 1);
		}
		else if (game->hp <= 0)
		{
			printText(20.0f, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f, 10, "Przegrales :(. Zacznij gre od nowa!", 1, 1, 1);
		}
		else
		{
			printText(80.0f, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f, 10, "Nie zdobyles wymaganej liczby punktow!", 1, 1, 1);
		}
	}

	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();
}

void OnReshape(int width, int height)
{
	h = height;
	w = width;

	const float aspectRatio = ((float)width) / height;
	float xSpan = 1;
	float ySpan = 1;

	if (aspectRatio > 1)
	{
		xSpan *= aspectRatio;
	}
	else
	{
		ySpan = xSpan / aspectRatio;
	}

	gluPerspective(60, (double)width / (double)height, 0.01f, 100.0f);
	glViewport(0, 0, width, height);
}
