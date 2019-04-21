#include "stdafx.h"
#include "Tutorial.h"


Tutorial::Tutorial(Train *t){
	train = t;
	this->player.pos.x = 0.0f;
	this->player.pos.y = 1.0f;
	this->player.pos.z = 3.0f;
}


Tutorial::~Tutorial()
{
}

void Tutorial::show(){
	if (frame == 1) {
		this->player.pos.x = 3 * cosf((timer*0.7f)*3.1415f / 180.0f);
		this->player.pos.z = 3 * sinf((timer*0.7f)*3.1415f / 180.0f);
		gluLookAt(this->player.pos.x, this->player.pos.y, this->player.pos.z, 0, 0, 0, 0.0f, 1.0f, 0.0f);
		printText(20, (glutGet(GLUT_WINDOW_HEIGHT) * 0.75f), 3, "Witaj w grze Zloty Pociag! Przed Toba 5 poziomow! Poznasz teraz zasady gry.", 1, 1, 1);
		train->showTrainByNumber(0);
	}
	else if (frame == 2) {
		this->player.pos.x = 4 - (5 * (timer / 400));
		this->player.pos.y = 0.5f;
		this->player.pos.z = 1.5f;
		gluLookAt(this->player.pos.x, this->player.pos.y, this->player.pos.z, 0, 0, 0, 0.0f, 1.0f, 0.0f);
		printText(20, (glutGet(GLUT_WINDOW_HEIGHT) * 0.75f), 3, "W grze bedziesz musial oddawac celne strzaly w kierunku pociagow.", 1, 1, 1);
		printText(20, (glutGet(GLUT_WINDOW_HEIGHT) * 0.75f)+20, 3, "Za zwykly pociag otrzymasz 50$ i punkty", 1, 1, 1);
		train->showTrainByNumber(0);
	}
	else if (frame == 3) {
		this->player.pos.x = 4 - (5 * (timer / 400));
		this->player.pos.y = 0.5f;
		this->player.pos.z = 1.5f;
		gluLookAt(this->player.pos.x, this->player.pos.y, this->player.pos.z, 0, 0, 0, 0.0f, 1.0f, 0.0f);
		printText(20, (glutGet(GLUT_WINDOW_HEIGHT) * 0.75f), 3, "Staraj sie nie strzelac do niebieskiego pociagu!", 1, 1, 1);
		printText(20, (glutGet(GLUT_WINDOW_HEIGHT) * 0.75f)+20, 3, "Z jego zniszczenie zostana Ci odebrane pieniadze i punkty.", 1, 1, 1);
		train->showTrainByNumber(1);
	}
	else if (frame == 4) {
		this->player.pos.x = 4 - (5 * (timer / 400));
		this->player.pos.y = 0.5f;
		this->player.pos.z = 1.5f;
		gluLookAt(this->player.pos.x, this->player.pos.y, this->player.pos.z, 0, 0, 0, 0.0f, 1.0f, 0.0f);
		printText(20, (glutGet(GLUT_WINDOW_HEIGHT) * 0.75f), 3, "Ten zielony pociag przewozi ogromna ilosc pieniedzy!", 1, 1, 1);
		printText(20, (glutGet(GLUT_WINDOW_HEIGHT) * 0.75f)+20, 3, "Z jego zniszczenie otrzymasz dodatkowe 150$ i punkty!", 1, 1, 1);
		train->showTrainByNumber(2);
	}
	else if (frame == 5) {
		this->player.pos.x = 4 - (5 * (timer / 400));
		this->player.pos.y = 0.5f;
		this->player.pos.z = 1.5f;
		gluLookAt(this->player.pos.x, this->player.pos.y, this->player.pos.z, 0, 0, 0, 0.0f, 1.0f, 0.0f);
		printText(20, (glutGet(GLUT_WINDOW_HEIGHT) * 0.75f), 3, "Zloty Pociag - Boss", 1, 1, 1);
		printText(20, (glutGet(GLUT_WINDOW_HEIGHT) * 0.75f)+20, 3, "Jego zniszczenie zakonczy gre. Uwaga! Pociag ten bedzie strzelac w Twoim kierunku!", 1, 1, 1);
		train->showTrainByNumber(3);
	}
	else if (frame == 6) {
		this->player.pos.x = 3 * cosf((timer*0.7f)*3.1415f / 180.0f);
		this->player.pos.y = 1.0f;
		this->player.pos.z = 3 * sinf((timer*0.7f)*3.1415f / 180.0f);
		gluLookAt(this->player.pos.x, this->player.pos.y, this->player.pos.z, 0, 0, 0, 0.0f, 1.0f, 0.0f);
		printText(20, (glutGet(GLUT_WINDOW_HEIGHT) * 0.75f), 3, "Zdobywaj punkty i przechodz do nastepnych poziomow!", 1, 1, 1);
		printText(20, (glutGet(GLUT_WINDOW_HEIGHT) * 0.75f)+20, 3, "Za zebrane pieniadze ulepszaj swoje dzialo! Powodzenia!", 1, 1, 1);
		train->showTrainByNumber(3);
	}
	else
		end = true;

	timer++;

	if (timer > 500) {
		timer = 0;
		frame++;
	}
}
