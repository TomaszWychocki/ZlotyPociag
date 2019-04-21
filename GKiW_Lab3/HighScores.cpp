#include "stdafx.h"
#include "HighScores.h"

HighScores::HighScores() :
	saved(false)
{
	getHighScores();

	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	back = ilutGLLoadImage("images/wstecz.jpg");
	bg = ilutGLLoadImage("images/menu_2.jpg");
}


HighScores::~HighScores()
{
}

void HighScores::saveScore(int points)
{
	if (!saved)
	{
		saved = true;
		int n = getNumber();

		std::ofstream scores;
		scores.open("scores.txt", std::ios::app);
		scores << n << " " << points << "\n";
		scores.close();
	}
}

void HighScores::getHighScores()
{
	std::ifstream scores;
	int player, points;
	scores.open("scores.txt");
	sc.clear();

	while (scores >> player >> points)
	{
		sc.push_back(std::make_pair(player, points));
	}

	for (size_t i = 0; i < sc.size(); i++)
	{
		for (size_t j = 0; j < sc.size() - 1; j++)
		{
			if (sc[j].second < sc[j + 1].second)
			{
				swap(sc[j], sc[j + 1]);
			}
		}
	}

	scores.close();
}

void HighScores::show()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float width = float(glutGet(GLUT_WINDOW_WIDTH));
	float height = float(glutGet(GLUT_WINDOW_HEIGHT));
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

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, bg);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);   glVertex2f(0, height);
		glTexCoord2f(0.0f, 1.0f);   glVertex2f(0, 0);
		glTexCoord2f(1.0f, 1.0f);   glVertex2f(width, 0);
		glTexCoord2f(1.0f, 0.0f);   glVertex2f(width, height);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, back);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(35, height - 35);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(35, height - (35 + 64));
		glTexCoord2f(1.0f, 1.0f); glVertex2f(293, height - (35 + 64));
		glTexCoord2f(1.0f, 0.0f); glVertex2f(293, height - 35);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);

	for (size_t i = 0; i < sc.size(); i++)
	{
		printText(200.0f, (i * 35.0f) + 50.0f, 3, "[GRACZ " + std::to_string(sc[i].first) + "] PUNKTY: " + std::to_string(sc[i].second), 1, 1, 0);
	}
}

int HighScores::getNumber()
{
	std::ifstream scores;
	scores.open("scores.txt");
	std::string line;
	int i = 1;

	while (getline(scores, line))
	{
		i++;
	}
	scores.close();

	return i;
}

int HighScores::checkItems(int x, int y)
{
	if ((y >= glutGet(GLUT_WINDOW_HEIGHT) - (35 + 64)) && (y <= glutGet(GLUT_WINDOW_HEIGHT) - 35) && (x >= 35) && (x <= 293))
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
