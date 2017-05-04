#include "stdafx.h"
#include "MainMenu.h"
#include "FunctionsPack.h"
#include <mmsystem.h>

MainMenu::MainMenu() {
	polygons[0].xmin = 410;
	polygons[0].xmax = 955;
	polygons[0].ymin = 230;
	polygons[0].ymax = 287;

	polygons[1].xmin = 410;
	polygons[1].xmax = 955;
	polygons[1].ymin = 327;
	polygons[1].ymax = 384;

	polygons[2].xmin = 410;
	polygons[2].xmax = 955;
	polygons[2].ymin = 422;
	polygons[2].ymax = 480;

	polygons[0].x1 = -2;
	polygons[0].x2 = 2;
	polygons[0].y1 = 1.25;
	polygons[0].y2 = 2.0;

	polygons[1].x1 = -2;
	polygons[1].x2 = 2;
	polygons[1].y1 = 0;
	polygons[1].y2 = 0.75;

	polygons[2].x1 = -2;
	polygons[2].x2 = 2;
	polygons[2].y1 = -1.25;
	polygons[2].y2 = -0.5;

	PlaySound("main.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	//BackgroundTexture = loadTexture();
	//TitleTexture = loadImage("Menu/MenuTitleFruit.png");
	//MenuItemsTexture = loadImage("Menu/MenuItems.png");
}


MainMenu::~MainMenu(){
	PlaySound(NULL, 0, 0);
}

void MainMenu::show() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glScalef(0.2, 0.2, 0.2);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);

	//glEnable(GL_TEXTURE_2D);
	//glEnable(GL_BLEND);
	//glBindTexture(GL_TEXTURE_2D, MenuFruitTexture);
	//glBegin(GL_QUADS);
	//	glTexCoord2f(0.0f, 0.0f);   glVertex2f(-4, -4);
	//	glTexCoord2f(0.0f, 1.0f);   glVertex2f(-4, 4);
	//	glTexCoord2f(1.0f, 1.0f);   glVertex2f(4, 4);
	//	glTexCoord2f(1.0f, 0.0f);   glVertex2f(4, -4);
	//glEnd();
	//glDisable(GL_BLEND);
	//glDisable(GL_TEXTURE_2D);

	//glEnable(GL_TEXTURE_2D);
	//glEnable(GL_BLEND);
	//glBindTexture(GL_TEXTURE_2D, MainTitleTexture);
	//glBegin(GL_QUADS);
	//glTexCoord2f(0.0f, 0.0f);   glVertex2f(-4.85, -9.0f);
	//glTexCoord2f(0.0f, 1.0f);   glVertex2f(-4.85, 4.0f);
	//glTexCoord2f(1.0f, 1.0f);   glVertex2f(7, 4.0f);
	//glTexCoord2f(1.0f, 0.0f);   glVertex2f(7, -9.0f);
	//glEnd();
	//glDisable(GL_BLEND);
	//glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, MenuItemsTexture);
	for (int i = 0; i<3; i++) {
		glBegin(GL_QUADS);
			/*glTexCoord2f(0.0f, 0.56f);*/  glVertex2f(polygons[i].x1, polygons[i].y1);
			/*glTexCoord2f(0.0f, 1.0f);*/   glVertex2f(polygons[i].x1, polygons[i].y2);
			/*glTexCoord2f(1.0f, 1.0f);*/   glVertex2f(polygons[i].x2, polygons[i].y2);
			/*glTexCoord2f(1.0f, 0.56f);*/  glVertex2f(polygons[i].x2, polygons[i].y1);
		glEnd();
	}

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	printText(glutGet(GLUT_WINDOW_WIDTH)/2 - 30, glutGet(GLUT_WINDOW_HEIGHT)/2 - 120, 10, "Start", 1, 0 ,0);
	printText(glutGet(GLUT_WINDOW_WIDTH) / 2 - 130, glutGet(GLUT_WINDOW_HEIGHT) / 2 - 20, 10, "Najlepsze wyniki", 1, 0, 0);
	printText(glutGet(GLUT_WINDOW_WIDTH) / 2 - 50, glutGet(GLUT_WINDOW_HEIGHT) / 2 + 75, 10, "Wyjscie", 1, 0, 0);
	glEnable(GL_LIGHTING);
}

int MainMenu::checkItems(int x, int y){
	for (int i = 0; i<3; i++) {
		if ((y >= polygons[i].ymin) && (y<polygons[i].ymax) && (x >= polygons[i].xmin) && (x <= polygons[i].xmax)) {
			return i;
			break;
		}
	}
	return -1;
}
