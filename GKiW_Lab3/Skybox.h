#pragma once
#include <IL/il.h> 
#include <IL/ilu.h> 
#include <IL/ilut.h>
#include <stdlib.h>

class Skybox
{
public:
	Skybox(float);
	~Skybox();
	void show();

private:
	GLuint front, back;
	GLuint up, down;
	GLuint left, right;

	GLuint frontFace, backFace;
	GLuint upFace, downFace;
	GLuint leftFace, rightFace;
	void CreateSkybox();
	float size;
};

