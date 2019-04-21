#pragma once

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
void GetRes(int&, int&);

enum state
{
	POST_LEVEL_SCREEN,
	PLAY,
	MAIN_MENU,
	HIGH_SCORES_SCREEN,
	CANNON_UPGRADE,
	LOADING_SCREEN
};

state CurrentState = MAIN_MENU;
MainMenu* m_menu;
CannonUpgradeMenu* cannonMenu;
Game* game;
HighScores* hs;
float Tm = 0.0, lastTm = 0.0;
int wait = 0;
int wait2 = 0;
float rot = 0;

int mouseX = 0, mouseY = 0;
float horizontalAngle = 0.0f;
float verticalAngle = 0.0f;
ISoundEngine* soundEngine;
