#include "stdafx.h"
#include "Collision.h"


Collision::Collision(char *fName, Train *t) {
	FILE *fp = fopen(fName, "r");
	float x, y, z;
	int w, k;

	while (!feof(fp))
	{
		fscanf(fp, "%d %d %f %f %f", &w, &k, &x, &y, &z);
		positions[w][k].push_back(vec3(x, y, z));
	}

	fclose(fp);

	train = t;
	trainMin.x = 0;
	trainMin.y = 0.44707;
	trainMin.z = -0.1278f;
	trainMax.x = 0;
	trainMax.y = 0.04497;
	trainMax.z = 0.1278f;
}


Collision::~Collision()
{
}

bool Collision::isCollision(float x, float y, float z) {
	int w = (int)abs(x);
	int k = (int)abs(z);
	float d = 0;

	if (w > wMax || k > kMax)
		return false;

	for (size_t i = 0; i < positions[w][k].size(); i++) {
		d = sqrt(pow(positions[w][k][i].x - x, 2) + pow(positions[w][k][i].y - y, 2) + pow(positions[w][k][i].z - z, 2));
		if (y <= 0.6f) {
			if (d < 0.10f)
				return true;
		}
		else {
			if (d < 0.35f)
				return true;
		}
	}

	return false;
}

bool Collision::isCollisionWithTrain(float x, float y, float z) {
	if (train->dir) {
		trainMin.x = train->posX - 0.26097f;
		trainMax.x = train->posX + 4.02643f;
	}
	else {
		trainMax.x = train->posX + 0.26097f;
		trainMin.x = train->posX - 4.02643f;
	}

	return (trainMin.x <= x && trainMax.x >= x) && (trainMin.y >= y && trainMax.y <= y) && (trainMin.z <= z && trainMax.z >= z);
}

void Collision::Render() {
	////Teren
	//for (int w = 0; w <= wMax; w++) {
	//	for (int k = 0; k <= kMax; k++) {
	//		for (size_t i = 0; i < positions[w][k].size(); i++) {
	//			glPushMatrix();
	//				glTranslatef(positions[w][k][i].x, positions[w][k][i].y, positions[w][k][i].z);
	//				glutSolidCube(0.05f);
	//			glPopMatrix();
	//		}
	//	}
	//}

	//Pociag
	glPushMatrix();
		glTranslatef(trainMin.x, trainMin.y, trainMax.z);
		glutSolidCube(0.1f);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(trainMin.x, trainMax.y, trainMax.z);
		glutSolidCube(0.1f);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(trainMin.x, trainMax.y, trainMin.z);
		glutSolidCube(0.1f);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(trainMin.x, trainMin.y, trainMin.z);
		glutSolidCube(0.1f);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(trainMax.x, trainMin.y, trainMax.z);
		glutSolidCube(0.1f);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(trainMax.x, trainMax.y, trainMax.z);
		glutSolidCube(0.1f);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(trainMax.x, trainMax.y, trainMin.z);
		glutSolidCube(0.1f);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(trainMax.x, trainMin.y, trainMin.z);
		glutSolidCube(0.1f);
	glPopMatrix();
}
