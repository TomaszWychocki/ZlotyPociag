#pragma once
#include <irrKlang.h>
#include <IL/il.h> 
#include <IL/ilu.h> 
#include <IL/ilut.h>
using namespace irrklang;

class CannonUpgradeMenu
{
public:
	CannonUpgradeMenu(Game*);
	~CannonUpgradeMenu();
	void show();
	int checkItems(int, int);

private:
	struct polygon
	{
		float xmin, xmax, ymin, ymax;
	};

	polygon polygons[5];
	Game *gam;

	long selectedMenu = -1;
	GLuint BackgroundTexture;
	GLuint exitItem;
	GLuint playItem;
	GLuint arrow;
	ISoundEngine* soundEngine;
	float height;
	float width;
};

