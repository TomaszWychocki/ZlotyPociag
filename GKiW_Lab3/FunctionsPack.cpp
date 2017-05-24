#include "FunctionsPack.h"
#include "stdafx.h"
#include <string>

void printText(float x, float y, int spacing, std::string str, float r, float g, float b) {
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glColor3f(r, g, b);
	glDisable(GL_LIGHTING);
	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, width, 0, height);
		glScalef(1, -1, 1);
		glTranslatef(0, -height, 0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();

			int x1 = x;

			for (std::string::iterator i = str.begin(); i != str.end(); ++i) {
				char c = *i;
				glRasterPos2f(x1, y);
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
				x1 = x1 + glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, c) + spacing;
			}

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
}

void drawViewfinder() {
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

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
}