#include "stdafx.h"
#include "Cannon.h"

Cannon::Cannon(){
	model = new Model("Cannon.3ds");
}


Cannon::~Cannon()
{
}

void Cannon::Render(){
	model->Render();
}
