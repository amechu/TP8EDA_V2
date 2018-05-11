#include "Menu.h"



Menu::Menu()
{
}


Menu::~Menu()
{
}

void const Menu::notify()
{
	drawer.update(this);
}

menuState const Menu::getState()
{
	return this->state;
}
