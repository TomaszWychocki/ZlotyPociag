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

void drawHUDelements(GLuint wf, GLuint bg) {
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

	glCallList(wf);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0, 0, 0, 0.5f);
	glCallList(bg);
	glDisable(GL_BLEND);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
}