#include "stdafx.h"
#include "Skybox.h"


Skybox::Skybox(float s) {
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	size = s;

	front = ilutGLLoadImage("images/skybox/front.png");
	back = ilutGLLoadImage("images/skybox/peaks_bk.jpg");
	up = ilutGLLoadImage("images/skybox/peaks_up.jpg");
	down = ilutGLLoadImage("images/skybox/peaks_dn.jpg");
	left = ilutGLLoadImage("images/skybox/left.png");
	right = ilutGLLoadImage("images/skybox/peaks_rt.jpg");

	CreateSkybox();
}


Skybox::~Skybox()
{
}

void Skybox::Render(){
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDisable(GL_FOG);

	glBindTexture(GL_TEXTURE_2D, front);
	glCallList(frontFace);

	glBindTexture(GL_TEXTURE_2D, left);
	glCallList(leftFace);

	glEnable(GL_FOG);
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


	backFace = glGenLists(1);
	glNewList(backFace, GL_COMPILE);
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
}
