#include "stdafx.h"
#include "Particle.h"


Particle::Particle(float x, float y, float z){
	startPos.x = x;
	startPos.y = y;
	startPos.z = z;

	//for (int i = 0; i < 100; i++) {
	//	float Theta = (rand() / (RAND_MAX / 6.28));
	//	float Phi = -1.57 + (rand() / (RAND_MAX / 3.14));
	//	par[i].x = 0.01f * cos(Theta) * sin(Phi);
	//	par[i].y = 0.01f * sin(Theta) * sin(Phi);
	//	par[i].z = 0.01f * cos(Phi);
	//}

	float theta = 0, phi = 0;
	int i = 0;
	float deltaTheta = 3.1415 / 10;
	float deltaPhi = 2 * 3.1415 / 10;
	for (int ring=0; ring < 10; ring++) {
		theta += deltaTheta;
		for (int point=0; point < 10; point++) {
			phi += deltaPhi;
			par[i].x = sin(phi) * cos(theta);
			par[i].y = sin(theta) * sin(phi);
			par[i].z = cos(phi);
			color[i].x = randMToN(0.6f, 1.0f);
			color[i].y = randMToN(0.3f, 0.7f);
			color[i].z = randMToN(0.0f, 0.3f);
			i++;
		}
	}
}

float Particle::randMToN(float M, float N) {
	return M + (rand() / (RAND_MAX / (N - M)));
}

Particle::~Particle() {
}

void Particle::show(){
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
		for (int i = 0; i < 100; i++) {
			glPushMatrix();
				glColor4f(color[i].x, color[i].y, color[i].z, (0.3 - Offset) / 0.3);
				glTranslatef(startPos.x + (par[i].x * Offset), startPos.y + (par[i].y * Offset), startPos.z + (par[i].z * Offset));
				glutSolidSphere(0.04, 5, 5);
			glPopMatrix();
		}

		glEnable(GL_LIGHTING);
		glDisable(GL_BLEND);
	glPopMatrix();

	Offset += 0.005;

	if (Offset > 0.3)
		end = true;
}
