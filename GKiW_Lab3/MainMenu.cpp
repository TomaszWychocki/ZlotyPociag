#include "stdafx.h"
#include "MainMenu.h"
#include "FunctionsPack.h"

MainMenu::MainMenu() {
	width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);

	polygons[0].xmin = 0 + ((width / 2) - 272);
	polygons[0].xmax = 545 + ((width / 2) - 272);
	polygons[0].ymin = 230;
	polygons[0].ymax = 287;

	polygons[1].xmin = 0 + ((width / 2) - 272);
	polygons[1].xmax = 545 + ((width / 2) - 272);
	polygons[1].ymin = 327;
	polygons[1].ymax = 384;

	polygons[2].xmin = 0 + ((width / 2) - 272);
	polygons[2].xmax = 545 + ((width / 2) - 272);
	polygons[2].ymin = 422;
	polygons[2].ymax = 480;

	se = createIrrKlangDevice();
	se->play2D("sounds/main.wav", true);

	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
	BackgroundTexture = ilutGLLoadImage("images/menu.jpg");
	startItem = ilutGLLoadImage("images/start.jpg");
	scoresItem = ilutGLLoadImage("images/naj.jpg");
	exitItem = ilutGLLoadImage("images/wyjscie2.jpg");
}


MainMenu::~MainMenu(){
	se->drop();
}

void MainMenu::show() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

			for (int i = 0; i<3; i++) {
				if (i == 0) glBindTexture(GL_TEXTURE_2D, startItem);
				if (i == 1) glBindTexture(GL_TEXTURE_2D, scoresItem);
				if (i == 2) glBindTexture(GL_TEXTURE_2D, exitItem);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f);  glVertex2f(polygons[i].xmin, polygons[i].ymax);
					glTexCoord2f(0.0f, 1.0f);  glVertex2f(polygons[i].xmin, polygons[i].ymin);
					glTexCoord2f(1.0f, 1.0f);  glVertex2f(polygons[i].xmax, polygons[i].ymin);
					glTexCoord2f(1.0f, 0.0f);  glVertex2f(polygons[i].xmax, polygons[i].ymax);
				glEnd();
			}
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
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
