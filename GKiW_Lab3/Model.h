#pragma once
#include "stdafx.h"
#include "Bitmap.h"
#include <vector>

struct SFace {
	int v[3];
	int n[3];
	int t[3];
};

class Model {
public:
	Model(char*, char*);
	~Model();
	void show();

private:
	void LoadObj(char*);
	GLuint LoadTexture(char*, int, int);
	GLuint dlId;
	GLuint textue;
};
