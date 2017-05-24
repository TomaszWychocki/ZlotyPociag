#pragma once
#include "Model.h"

class Cannon
{
public:
	Cannon();
	~Cannon();
	void Render();
	Model *model;
	int fireRate = 6;
	int ballPower = 20;
	int ballSpeed = 7;
	//CannonModel

	//Timer
	int reloading = 0;

	//Price
	int fireRatePrices[5] = { 200,500,700,1000,1200 };
	int ballPowerPrices[5] = { 50,100,200,300,500 };
	int ballSpeedPrices[5] = { 400,500,600,700,1000 };
	
	//Levels
	int fireRateLevel = 1;
	int ballPowerLevel = 1;
	int ballSpeedLevel = 1;
};

