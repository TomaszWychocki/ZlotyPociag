#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <IL/il.h> 
#include <IL/ilu.h> 
#include <IL/ilut.h>
#include "FunctionsPack.h"


class HighScores
{
public:
	HighScores();
	~HighScores();
	void saveScore(int points);
	void getHighScores();
	void show();
	int checkItems(int, int);

private:
	int getNumber();
	std::vector<std::pair<int, int>> sc;
	bool saved;
	GLuint back;
	GLuint bg;
};

