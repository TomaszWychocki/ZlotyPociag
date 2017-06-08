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

void drawHUDelements(GLuint wf, GLuint bg, float loading, float Hp) {
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

	//Ladowanie pocisku
	if (loading > 0) {
		glColor3f(1, 1.0f - loading, 0);
		glBegin(GL_QUADS);
			glVertex2f((width / 2) - 30, (height / 2) - 40 + (1 - loading) * 60);
			glVertex2f((width / 2) - 35, (height / 2) - 40 + (1 - loading) * 60);
			glVertex2f((width / 2) - 35, (height / 2) + 20);
			glVertex2f((width / 2) - 30, (height / 2) + 20);
		glEnd();
	}

	//Hp pociagu
	glColor3f(1 - Hp, 0.75f * Hp, 0);
	glBegin(GL_QUADS);
		glVertex2f((width / 2) + 30, (height / 2) - 40 + (1 - Hp) * 60);
		glVertex2f((width / 2) + 35, (height / 2) - 40 + (1 - Hp) * 60);
		glVertex2f((width / 2) + 35, (height / 2) + 20);
		glVertex2f((width / 2) + 30, (height / 2) + 20);
	glEnd();

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

void printLoading(std::string s) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	printText(20, glutGet(GLUT_WINDOW_HEIGHT) / 2, 10, "Wczytywanie - " + s + "%", 1, 1, 1);
	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();
}
