#include "stdafx.h"
#include "Game.h"
#include "CannonUpgradeMenu.h"
#include "FunctionsPack.h"
#include <string.h>

CannonUpgradeMenu::CannonUpgradeMenu(Game *g) {
	this->gam = g;

	polygons[0].xmin = 695;
	polygons[0].xmax = 732;
	polygons[0].ymin = 292;
	polygons[0].ymax = 329;

	polygons[1].xmin = 695;
	polygons[1].xmax = 732;
	polygons[1].ymin = 347;
	polygons[1].ymax = 384;

	polygons[2].xmin = 695;
	polygons[2].xmax = 732;
	polygons[2].ymin = 402;
	polygons[2].ymax = 439;

	polygons[3].xmin = 35;
	polygons[3].xmax = 293;
	polygons[3].ymin = 596;
	polygons[3].ymax = 660;

	polygons[4].xmin = 1067;
	polygons[4].xmax = 1325;
	polygons[4].ymin = 596;
	polygons[4].ymax = 660;

	se = createIrrKlangDevice();
	se->play2D("sounds/main.wav", true);
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
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

			for (int i = 0; i<5; i++) {
				glBegin(GL_LINE_LOOP);
				glVertex2f(polygons[i].xmin, polygons[i].ymin);
				glVertex2f(polygons[i].xmin, polygons[i].ymax);
				glVertex2f(polygons[i].xmax, polygons[i].ymax);
				glVertex2f(polygons[i].xmax, polygons[i].ymin);
				glEnd();
			}

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);

	printText(320, 317, 6, "Szybkostrzelnosc: lvl " + std::to_string(gam->cannon->fireRateLevel), 1, 1, 0);
	if(gam->cannon->fireRateLevel < 5)
		printText(740, 317, 6, "$" + std::to_string(gam->cannon->fireRatePrices[gam->cannon->fireRateLevel-1]), 1, 1, 0);
	else
		printText(740, 317, 6, "MAX", 1, 1, 0);

	printText(320, 372, 6, "Moc pocisku: lvl " + std::to_string(gam->cannon->ballPowerLevel), 1, 1, 0);
	if (gam->cannon->ballPowerLevel < 5)
		printText(740, 372, 6, "$" + std::to_string(gam->cannon->ballPowerPrices[gam->cannon->ballPowerLevel - 1]), 1, 1, 0);
	else
		printText(740, 372, 6, "MAX", 1, 1, 0);

	printText(320, 427, 6, "Predkosc pocisku: lvl " + std::to_string(gam->cannon->ballSpeedLevel), 1, 1, 0);
	if (gam->cannon->ballSpeedLevel < 5)
		printText(740, 427, 6, "$" + std::to_string(gam->cannon->ballSpeedPrices[gam->cannon->ballSpeedLevel - 1]), 1, 1, 0);
	else
		printText(740, 427, 6, "MAX", 1, 1, 0);

	printText(100, 40, 6, "Poziom: " + std::to_string(gam->currentLevel), 1, 1, 0);
	printText(100, 60, 6, "Punkty: " + std::to_string(gam->points), 1, 1, 0);
	printText(100, 80, 6, "Pieniadze: $" + std::to_string(gam->cash), 1, 1, 0);
	printText(100, 120, 6, gam->message, 1, 0, 0);

	printText(115, 635, 6, "Wyjscie", 1, 1, 0);
	printText(1130, 635, 6, "Graj dalej", 1, 1, 0);
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
