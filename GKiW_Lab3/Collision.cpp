#include "stdafx.h"
#include "Point.h"
#include "Collision.h"


Collision::Collision(char *fName, Train *train) :
	trainMin(0, 0.44707f, -0.1278f),
	trainMax(0, 0.04497f, 0.1278f)
{
	FILE *fp = fopen(fName, "r");
	float x, y, z;
	int w, k;

	while (!feof(fp))
	{
		fscanf(fp, "%d %d %f %f %f", &w, &k, &x, &y, &z);
		this->positions[w][k].push_back(Point(x, y, z));
	}

	fclose(fp);

	this->train = train;
}


Collision::~Collision()
{
}

bool Collision::isCollision(const Point & point)
{
	size_t w = (size_t)abs(point.x);
	size_t k = (size_t)abs(point.z);
	float distance = 0;

	if (w > this->wMax || k > this->kMax)
	{
		return false;
	}

	for (const Point & terrainPoint : this->positions[w][k])
	{
		distance = terrainPoint.distanceTo(point);

		if ((point.y <= 0.6f && distance < 0.10f) || distance < 0.35f)
		{
			return true;
		}
	}

	return false;
}

bool Collision::isCollisionWithTrain(const Point & point)
{
	if (this->train->dir)
	{
		this->trainMin.x = this->train->posX - 0.26097f;
		this->trainMax.x = this->train->posX + 4.02643f;
	}
	else
	{
		this->trainMax.x = this->train->posX + 0.26097f;
		this->trainMin.x = this->train->posX - 4.02643f;
	}

	return (trainMin.x <= point.x && trainMax.x >= point.x) && 
		   (trainMin.y >= point.y && trainMax.y <= point.y) && 
		   (trainMin.z <= point.z && trainMax.z >= point.z);
}

void Collision::show()
{
	//Teren
	for (size_t w = 0; w <= wMax; w++)
	{
		for (size_t k = 0; k <= kMax; k++)
		{
			for (const Point & terrainPoint : this->positions[w][k])
			{
				glPushMatrix();
					glTranslatef(terrainPoint.x, terrainPoint.y, terrainPoint.z);
					glutSolidCube(0.05f);
				glPopMatrix();
			}
		}
	}

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
