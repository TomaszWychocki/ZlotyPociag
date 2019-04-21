#include "stdafx.h"
#include "Skybox.h"


Skybox::Skybox(float s) {
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	size = s;

	front = ilutGLLoadImage("images/skybox/desertsky_ft.jpg");
	back = ilutGLLoadImage("images/skybox/desertsky_bk.jpg");
	up = ilutGLLoadImage("images/skybox/desertsky_up.jpg");
	down = ilutGLLoadImage("images/skybox/desertsky_dn.jpg");
	left = ilutGLLoadImage("images/skybox/desertsky_lf.jpg");
	right = ilutGLLoadImage("images/skybox/desertsky_rt.jpg");

	CreateSkybox();
}


Skybox::~Skybox()
{
}

void Skybox::show(){
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glDisable(GL_FOG);

	glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);

		glBindTexture(GL_TEXTURE_2D, front);
		glCallList(frontFace);

		glBindTexture(GL_TEXTURE_2D, left);
		glCallList(leftFace);

		glBindTexture(GL_TEXTURE_2D, right);
		glCallList(rightFace);

		glBindTexture(GL_TEXTURE_2D, back);
		glCallList(backFace);

		glBindTexture(GL_TEXTURE_2D, up);
		glCallList(upFace);

		glBindTexture(GL_TEXTURE_2D, down);
		glCallList(downFace);
	glPopMatrix();

	//glEnable(GL_FOG);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDisable(GL_TEXTURE_2D);
}

void Skybox::CreateSkybox(){
	frontFace = glGenLists(1);
	glNewList(frontFace, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-size, size, -size);

			glTexCoord2f(0.0f, 0.0f);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-size, 0.0f, -size);

			glTexCoord2f(1.0f, 0.0f);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(size, 0.0f, -size);

			glTexCoord2f(1.0f, 1.0f);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(size, size, -size);
		glEnd();
	glEndList();

	leftFace = glGenLists(1);
	glNewList(leftFace, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-size, 0.0f, -size);

			glTexCoord2f(0.0f, 0.0f);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-size, size, -size);

			glTexCoord2f(1.0f, 0.0f);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-size, size, size);

			glTexCoord2f(1.0f, 1.0f);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-size, 0.0f, size);
		glEnd();
	glEndList();

	rightFace = glGenLists(1);
		glNewList(rightFace, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(size, size, -size);

			glTexCoord2f(0.0f, 0.0f);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(size, 0.0f, -size);

			glTexCoord2f(1.0f, 0.0f);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(size, 0.0f, size);

			glTexCoord2f(1.0f, 1.0f);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(size, size, size);
		glEnd();
	glEndList();


	backFace = glGenLists(1);
	glNewList(backFace, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-size, 0.0f, size);

			glTexCoord2f(0.0f, 0.0f);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-size, size, size);

			glTexCoord2f(1.0f, 0.0f);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(size, size, size);

			glTexCoord2f(1.0f, 1.0f);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(size, 0.0f, size);
		glEnd();
	glEndList();

	upFace = glGenLists(1);
		glNewList(upFace, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f(-size, size, size);

			glTexCoord2f(0.0f, 0.0f);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f(-size, size, -size);

			glTexCoord2f(1.0f, 0.0f);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f(size, size, -size);

			glTexCoord2f(1.0f, 1.0f);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f(size, size, size);
		glEnd();
	glEndList();

	downFace = glGenLists(1);
	glNewList(downFace, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-size, 0.0f, -size);

			glTexCoord2f(0.0f, 0.0f);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-size, 0.0f, size);

			glTexCoord2f(1.0f, 0.0f);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(size, 0.0f, size);

			glTexCoord2f(1.0f, 1.0f);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(size, 0.0f, -size);
		glEnd();
	glEndList();
}
