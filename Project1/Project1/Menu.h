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

	bool const getParserError();
	bool const getFilesystemError();
	bool loadImages();
	bool loadENCD();

	menuState const getState();
	menuError const getError();
	
	void setParserError(bool error);
	void setFilesystemError(bool error);
	void setImageError(bool error);
	void setENCDError(bool error);
	void setState(menuState state_);
	void setError(menuError error_);
	
	void checkError();
	void reportError();
	void loopMenu();
	void loopEncoder();
	bool encode();
	void loopDecoder();
	bool decode();
	



private:
	std::vector<Page> pages;
	std::string dirPath;
	Drawer drawer;
	menuState state = menuState::MAINMENU;
	menuError error = menuError::NO_ERROR;
	bool parserError;
	bool filesystemError;
};

