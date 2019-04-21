#pragma once
#include <irrKlang.h>
#include <IL/il.h> 
#include <IL/ilu.h> 
#include <IL/ilut.h>
using namespace irrklang;

class MainMenu
{
public:
	MainMenu();
	~MainMenu();
	void show();
	int checkItems(int, int);

private:
	typedef struct polygon
	{
		float xmin, xmax, ymin, ymax;
	} polygon;

	polygon polygons[3];
	long selectedMenu = -1;
	GLuint BackgroundTexture;
	GLuint startItem;
	GLuint scoresItem;
	GLuint exitItem;
	ISoundEngine* soundEngine;
	float width;
	float height;
};

