#include "stdafx.h"
#include "Cannon.h"

Cannon::Cannon()
{
	model = new Model("models\\Cannon.obj", "models\\textures\\Cannon.bmp");
}


Cannon::~Cannon()
{
}

void Cannon::show()
{
	model->show();
}
