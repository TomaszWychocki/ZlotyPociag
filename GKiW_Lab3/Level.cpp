#include "stdafx.h"
#include "Level.h"


Level::Level(int n) {
	levelNumber = n;
	requiredPoints = maxPoints[levelNumber - 1];
	wind = windValues[levelNumber - 1];
	maxTime = maxTimes[levelNumber - 1];
	sX = startPosX[levelNumber - 1];
	sZ = startPosZ[levelNumber - 1];
	startTime = glutGet(GLUT_ELAPSED_TIME)/1000;
	curentPoints = 0;
	curentCash = 0;
}


Level::~Level() {
}

int Level::getRemainingTime() {
	return maxTime - ((glutGet(GLUT_ELAPSED_TIME) / 1000) - startTime);
}
