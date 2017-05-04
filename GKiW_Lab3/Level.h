#pragma once
class Level
{
public:
	Level(int);
	~Level();
	int levelNumber;
	int maxTime;
	int requiredPoints;
	int curentPoints;
	int curentCash;
	float wind;

	int getRemainingTime();

private:
	//int maxTimes[5] = { 60,50,40,40,100 };
	//int maxPoints[5] = { 100,150,180,220,9999 };
	int maxTimes[5] = { 30,25,20,20,50 };
	int maxPoints[5] = { 1,2,3,4,5 };
	float windValues[5] = { 0,0.001f,0.002f,0.003f,0.004f };
	float startTime;
};

