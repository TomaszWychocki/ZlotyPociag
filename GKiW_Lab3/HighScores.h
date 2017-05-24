#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FunctionsPack.h"
#include <IL/il.h> 
#include <IL/ilu.h> 
#include <IL/ilut.h>

using namespace std;

class HighScores
{
public:
	HighScores();
	~HighScores();
	void saveScore(int points);
	void getHighScores();
	void Render();
	int checkItems(int, int);

private:
	int getNumber();
	vector<pair<int, int>> sc;
	bool saved = false;
	GLuint back;
	GLuint bg;
};

