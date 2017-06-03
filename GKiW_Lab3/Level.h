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
	int trainPoint;
	float trainSpeed;
	float wind;
	float sX;
	float sZ;

	int getRemainingTime();

private:
	int maxTimes[5] = { 60,50,40,40,100 };
	int maxPoints[5] = { 100,150,180,220,1000 };
	//int maxPoints[5] = { 1,2,3,4,5 };
	int trainPoints[5] = { 12, 16, 20, 22, 2000 };
	float windValues[5] = { 0,0.001f,0.002f,0.003f,0.004f };
	float startPosX[5] = { -2, 2, 3, 0, 2 };
	float startPosZ[5] = { 7, 10, 12, 14, 16 };
	float tSpeed[5] = { 0.4f, 0.6f, 0.8f, 1.0f, 1.5f };
	float startTime;
};

