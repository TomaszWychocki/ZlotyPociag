void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnKeyUp(unsigned char, int, int);
void OnSpecialKeyPress(int, int, int);
void OnSpecialKeyDown(int, int, int);
void OnSpecialKeyUp(int, int, int);
void OnMove(int, int);
void onMouseButton(int, int, int, int);
void OnTimer(int);

enum state {
	postLevel, play, menu, highscore, cannonUpgrade
};

struct vec3 {
	float x, y, z;
};

state CurrentState = menu;
MainMenu* m_menu;
CannonUpgradeMenu* cannonMenu;
Game* game;
double Tm = 0.0;
int wait = 0;
int wait2 = 0;
float rot = 0;

int mouseX = 0, mouseY = 0;
float horizontalAngle = 0.0f;
float verticalAngle = 0.0f;
