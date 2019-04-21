#include "stdafx.h"
#include "Game.h"
#include "CannonUpgradeMenu.h"
#include "FunctionsPack.h"
#include <string.h>

CannonUpgradeMenu::CannonUpgradeMenu(Game *g)
{
	this->gam = g;
	width = float(glutGet(GLUT_WINDOW_WIDTH));
	height = float(glutGet(GLUT_WINDOW_HEIGHT));

	polygons[0].xmin = (width / 2.0f) + 126.0f;
	polygons[0].xmax = (width / 2.0f) + 163.0f;
	polygons[0].ymin = 292.0f;
	polygons[0].ymax = 329.0f;

	polygons[1].xmin = (width / 2.0f) + 126.0f;
	polygons[1].xmax = (width / 2.0f) + 163.0f;
	polygons[1].ymin = 347.0f;
	polygons[1].ymax = 384.0f;

	polygons[2].xmin = (width / 2.0f) + 126.0f;
	polygons[2].xmax = (width / 2.0f) + 163.0f;
	polygons[2].ymin = 402.0f;
	polygons[2].ymax = 439.0f;

	polygons[3].xmin = 35.0f; //wyjscie
	polygons[3].xmax = 293.0f;
	polygons[3].ymin = height - (35.0f + 64.0f);
	polygons[3].ymax = height - 35.0f;

	polygons[4].xmin = width - (35.0f + 258.0f); //graj dalej
	polygons[4].xmax = width - 35.0f;
	polygons[4].ymin = height - (35.0f + 64.0f);
	polygons[4].ymax = height - 35.0f;

	soundEngine = createIrrKlangDevice();
	soundEngine->play2D("sounds/main.wav", true);
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
	BackgroundTexture = ilutGLLoadImage("images/menu_2.jpg");
	exitItem = ilutGLLoadImage("images/wyjscie.jpg");
	playItem = ilutGLLoadImage("images/graj_dalej.jpg");
	arrow = ilutGLLoadImage("images/up_arrow.jpg");
}


CannonUpgradeMenu::~CannonUpgradeMenu()
{
	soundEngine->drop();
}

void CannonUpgradeMenu::show()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float width = float(glutGet(GLUT_WINDOW_WIDTH));
	float height = float((GLUT_WINDOW_HEIGHT));
	glMatrixMode(GL_PROJECTION);
	glColor3f(1, 1, 1);
	glDisable(GL_LIGHTING);
	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, width, 0, height);
		glScalef(1, -1, 1);
		glTranslatef(0.0f, -height, 0.0f);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, BackgroundTexture);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f);   glVertex2f(0, height);
				glTexCoord2f(0.0f, 1.0f);   glVertex2f(0, 0);
				glTexCoord2f(1.0f, 1.0f);   glVertex2f(width, 0);
				glTexCoord2f(1.0f, 0.0f);   glVertex2f(width, height);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, arrow);
			for (int i = 0; i<=2; i++)
			{
				glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f);  glVertex2f(polygons[i].xmin, polygons[i].ymax);
					glTexCoord2f(0.0f, 1.0f);  glVertex2f(polygons[i].xmin, polygons[i].ymin);
					glTexCoord2f(1.0f, 1.0f);  glVertex2f(polygons[i].xmax, polygons[i].ymin);
					glTexCoord2f(1.0f, 0.0f);  glVertex2f(polygons[i].xmax, polygons[i].ymax);
				glEnd();
			}

			glBindTexture(GL_TEXTURE_2D, exitItem);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f);  glVertex2f(polygons[3].xmin, polygons[3].ymax);
				glTexCoord2f(0.0f, 1.0f);  glVertex2f(polygons[3].xmin, polygons[3].ymin);
				glTexCoord2f(1.0f, 1.0f);  glVertex2f(polygons[3].xmax, polygons[3].ymin);
				glTexCoord2f(1.0f, 0.0f);  glVertex2f(polygons[3].xmax, polygons[3].ymax);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, playItem);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f);  glVertex2f(polygons[4].xmin, polygons[4].ymax);
				glTexCoord2f(0.0f, 1.0f);  glVertex2f(polygons[4].xmin, polygons[4].ymin);
				glTexCoord2f(1.0f, 1.0f);  glVertex2f(polygons[4].xmax, polygons[4].ymin);
				glTexCoord2f(1.0f, 0.0f);  glVertex2f(polygons[4].xmax, polygons[4].ymax);
			glEnd();

			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);

	printText((width / 2.0f) - 250.0f, 317.0f, 6, "Szybkostrzelnosc: lvl " + std::to_string(gam->cannon->fireRateLevel), 1, 1, 0);
	if(gam->cannon->fireRateLevel < 5)
		printText((width / 2.0f) + 170.0f, 317.0f, 6, "$" + std::to_string(gam->cannon->fireRatePrices[gam->cannon->fireRateLevel-1]), 1, 1, 0);
	else
		printText((width / 2.0f) + 170.0f, 317.0f, 6, "MAX", 1, 1, 0);

	printText((width / 2.0f) - 250.0f, 372.0f, 6, "Moc pocisku: lvl " + std::to_string(gam->cannon->ballPowerLevel), 1, 1, 0);
	if (gam->cannon->ballPowerLevel < 5)
		printText((width / 2.0f) + 170.0f, 372.0f, 6, "$" + std::to_string(gam->cannon->ballPowerPrices[gam->cannon->ballPowerLevel - 1]), 1, 1, 0);
	else
		printText((width / 2.0f) + 17.0f, 372.0f, 6, "MAX", 1, 1, 0);

	printText((width / 2.0f) - 250.0f, 427.0f, 6, "Predkosc pocisku: lvl " + std::to_string(gam->cannon->ballSpeedLevel), 1, 1, 0);
	if (gam->cannon->ballSpeedLevel < 5)
		printText((width / 2.0f) + 170.0f, 427.0f, 6, "$" + std::to_string(gam->cannon->ballSpeedPrices[gam->cannon->ballSpeedLevel - 1]), 1, 1, 0);
	else
		printText((width / 2.0f) + 170.0f, 427.0f, 6, "MAX", 1, 1, 0);

	printText(100.0f, 40.0f, 6, "Poziom: " + std::to_string(gam->currentLevel), 1, 1, 0);
	printText(100.0f, 60.0f, 6, "Punkty: " + std::to_string(gam->points), 1, 1, 0);
	printText(100.0f, 80.0f, 6, "Pieniadze: $" + std::to_string(gam->cash), 1, 1, 0);
	printText(100.0f, 120.0f, 6, gam->message, 1, 0, 0);
}

int CannonUpgradeMenu::checkItems(int x, int y)
{
	for (int i = 0; i<5; i++)
	{
		if ((y >= polygons[i].ymin) && (y<polygons[i].ymax) && (x >= polygons[i].xmin) && (x <= polygons[i].xmax))
		{
			return i;
			break;
		}
	}
	return -1;
}
