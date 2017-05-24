#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FunctionsPack.h"

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
};

