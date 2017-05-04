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
	GLuint TitleTexture;
	GLuint MenuItemsTexture;
};

