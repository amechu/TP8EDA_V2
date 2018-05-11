#pragma once

#include "Page.h"
#include "Drawer.h"
#include <vector>

enum class menuError { BAD_PARSER, BAD_FILEREADER, BAD_IMAGE, BAD_ENCD , NO_ERROR};
enum class menuState { MAINMENU, ENCODER, DECODER, SUCCESS, ERROR, QUIT };

class Menu
{
public:
	Menu();
	~Menu();
	void const notify();
	menuState const getState();
	void setParserError(bool error);
	bool const getParserError();
	void setFilesystemError(bool error);
	bool const getFilesystemError();
	void setState(menuState state_);
	void setError(menuError error_);
	void checkError();

private:
	std::vector<Page> pages;
	std::string dirPath;
	Drawer drawer;
	menuState state = menuState::MAINMENU;
	menuError error = menuError::NO_ERROR;
	bool parserError;
	bool filesystemError;
};

