#pragma once
#include <irrKlang.h>
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
		float x1, y1, x2, y2;
		int xmin, xmax, ymin, ymax;
	} polygon;

	polygon polygons[3];
	long selectedMenu = -1;
	GLuint BackgroundTexture;
	GLuint TitleTexture;
	GLuint MenuItemsTexture;
	ISoundEngine* se;
};

