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
	typedef struct polygon
	{
		int xmin, xmax, ymin, ymax;
	} polygon;

	polygon polygons[5];
	Game *gam;

	long selectedMenu = -1;
	GLuint BackgroundTexture;
	GLuint exitItem;
	GLuint playItem;
	GLuint arrow;
	ISoundEngine* se;
	int height;
	int width;
};

