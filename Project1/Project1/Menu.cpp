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

void Menu::setParserError(bool error)
{
	parserError = error;
}

bool const Menu::getParserError()
{
	return parserError;
}

void Menu::setFilesystemError(bool error)
{
	filesystemError = error;
}

bool const Menu::getFilesystemError()
{
	return filesystemError;
}

void Menu::setState(menuState state_)
{
	state = state_;
}
