#pragma once

#include "Page.h"
#include "Drawer.h"
#include <vector>

enum class menuError { BAD_THRESHHOLD, BAD_PATH, NO_IMAGES, NO_ENCD, BAD_IMAGE, BAD_ENCD , NO_ERROR};
enum class menuState { MAINMENU, ENCODER, DECODER, SUCCESS, ERROR };

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

private:
	std::vector<Page> pages;
	std::string dirPath;
	Drawer drawer;
	menuState state = menuState::MAINMENU;
	menuError error = menuError::NO_ERROR;
	bool parserError;
	bool filesystemError;
};

