#include "stdafx.h"
#include "HighScores.h"

HighScores::HighScores(){
	getHighScores();
}


HighScores::~HighScores()
{
}

void HighScores::saveScore(int points) {
	if (!saved) {
		saved = true;
		int n = getNumber();

		ofstream scores;
		scores.open("scores.txt", ios::app);
		scores << n << " " << points << "\n";
		scores.close();
	}
}

void HighScores::getHighScores() {
	ifstream scores;
	int player, points;
	scores.open("scores.txt");
	sc.clear();

	while (scores >> player >> points) {
		sc.push_back(make_pair(player, points));
	}

	for (int i = 0; i < sc.size(); i++) {
		for (int j = 0; j < sc.size() - 1; j++) {
			if (sc[j].second < sc[j + 1].second)
				swap(sc[j], sc[j + 1]);
		}
	}

	scores.close();
}

void HighScores::Render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glColor3f(1, 1, 1);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glScalef(1, -1, 1);
	glTranslatef(0, -height, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glBegin(GL_LINE_LOOP);
		glVertex2f(35, 596);
		glVertex2f(35, 660);
		glVertex2f(293, 660);
		glVertex2f(293, 596);
	glEnd();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);

	printText(115, 635, 6, "Wstecz", 1, 1, 0);

	for (size_t i = 0; i < sc.size(); i++) {
		printText(200, (i*35) + 50, 3, "[GRACZ " + std::to_string(sc[i].first) + "] PUNKTY: " + std::to_string(sc[i].second), 1, 1, 0);
	}
}

int HighScores::getNumber() {
	ifstream scores;
	scores.open("scores.txt");
	string line;
	int i = 1;
	while (getline(scores, line))
		i++;
	scores.close();
	return i;
}

int HighScores::checkItems(int x, int y) {
	if ((y >= 596) && (y<=660) && (x >= 35) && (x <= 293)) 
		return 1;
	else
		return -1;
}
