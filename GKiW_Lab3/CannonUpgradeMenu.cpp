#include "stdafx.h"
#include "Game.h"
#include "CannonUpgradeMenu.h"
#include "FunctionsPack.h"
#include <string.h>

CannonUpgradeMenu::CannonUpgradeMenu(Game *g) {
	this->gam = g;
	width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);

	polygons[0].xmin = (width / 2) + 126;
	polygons[0].xmax = (width / 2) + 163;
	polygons[0].ymin = 292;
	polygons[0].ymax = 329;

	polygons[1].xmin = (width / 2) + 126;
	polygons[1].xmax = (width / 2) + 163;
	polygons[1].ymin = 347;
	polygons[1].ymax = 384;

	polygons[2].xmin = (width / 2) + 126;
	polygons[2].xmax = (width / 2) + 163;
	polygons[2].ymin = 402;
	polygons[2].ymax = 439;

	polygons[3].xmin = 35; //wyjscie
	polygons[3].xmax = 293;
	polygons[3].ymin = height - (35 + 64);
	polygons[3].ymax = height - 35;

	polygons[4].xmin = width - (35 + 258); //graj dalej
	polygons[4].xmax = width - 35;
	polygons[4].ymin = height - (35 + 64);
	polygons[4].ymax = height - 35;

	se = createIrrKlangDevice();
	se->play2D("sounds/main.wav", true);
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


CannonUpgradeMenu::~CannonUpgradeMenu() {
	se->drop();
}

void CannonUpgradeMenu::show() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glColor3f(1, 1, 1);
	glDisable(GL_LIGHTING);
	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, width, 0, height);
		glScalef(1, -1, 1);
		glTranslatef(0, -height, 0);
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
			for (int i = 0; i<=2; i++) {
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

	printText((width/2) - 250, 317, 6, "Szybkostrzelnosc: lvl " + std::to_string(gam->cannon->fireRateLevel), 1, 1, 0);
	if(gam->cannon->fireRateLevel < 5)
		printText((width / 2) + 170, 317, 6, "$" + std::to_string(gam->cannon->fireRatePrices[gam->cannon->fireRateLevel-1]), 1, 1, 0);
	else
		printText((width / 2) + 170, 317, 6, "MAX", 1, 1, 0);

	printText((width / 2) - 250, 372, 6, "Moc pocisku: lvl " + std::to_string(gam->cannon->ballPowerLevel), 1, 1, 0);
	if (gam->cannon->ballPowerLevel < 5)
		printText((width / 2) + 170, 372, 6, "$" + std::to_string(gam->cannon->ballPowerPrices[gam->cannon->ballPowerLevel - 1]), 1, 1, 0);
	else
		printText((width / 2) + 170, 372, 6, "MAX", 1, 1, 0);

	printText((width / 2) - 250, 427, 6, "Predkosc pocisku: lvl " + std::to_string(gam->cannon->ballSpeedLevel), 1, 1, 0);
	if (gam->cannon->ballSpeedLevel < 5)
		printText((width / 2) + 170, 427, 6, "$" + std::to_string(gam->cannon->ballSpeedPrices[gam->cannon->ballSpeedLevel - 1]), 1, 1, 0);
	else
		printText((width / 2) + 170, 427, 6, "MAX", 1, 1, 0);

	printText(100, 40, 6, "Poziom: " + std::to_string(gam->currentLevel), 1, 1, 0);
	printText(100, 60, 6, "Punkty: " + std::to_string(gam->points), 1, 1, 0);
	printText(100, 80, 6, "Pieniadze: $" + std::to_string(gam->cash), 1, 1, 0);
	printText(100, 120, 6, gam->message, 1, 0, 0);
}

int CannonUpgradeMenu::checkItems(int x, int y) {
	for (int i = 0; i<5; i++) {
		if ((y >= polygons[i].ymin) && (y<polygons[i].ymax) && (x >= polygons[i].xmin) && (x <= polygons[i].xmax)) {
			return i;
			break;
		}
	}
	return -1;
}
