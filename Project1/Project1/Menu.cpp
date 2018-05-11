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

menuError const Menu::getError()
{
	return this->error;
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

void Menu::setImageError(bool error)
{
}

void Menu::setENCDError(bool error)
{
}

bool const Menu::getFilesystemError()
{
	return filesystemError;
}

bool Menu::loadImages()
{
	return false;
}

bool Menu::loadENCD()
{
	return false;
}

void Menu::setState(menuState state_)
{
	state = state_;
}

void Menu::setError(menuError error_)
{
	error = error;
}

void Menu::reportError()
{
}

void Menu::loopMenu()
{
}

void Menu::loopEncoder()
{
}

bool Menu::encode()
{
	return false;
}

void Menu::loopDecoder()
{
}

bool Menu::decode()
{
	return false;
}

void Menu::checkError()
{
	if (getFilesystemError()) {
		setError(menuError::BAD_FILEREADER);
	}
	if (getParserError()) {
		setError(menuError::BAD_PARSER);
	}
}
