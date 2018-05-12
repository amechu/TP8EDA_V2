#pragma once

class allegro_c;

#include "Page.h"
#include "Drawer.h"
#include <vector>

enum class menuError { BAD_PARSER, BAD_FILEREADER, BAD_IMAGE, BAD_ENCD , NO_ERROR};


class Menu {
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
	void loadAllegroClass(allegro_c * alClass_);

	void checkError();
	void reportError();
	void loopMenu(ALLEGRO_EVENT_QUEUE * evq);
	void loopEncoder(ALLEGRO_EVENT_QUEUE * evq);
	bool encode();
	void loopDecoder(ALLEGRO_EVENT_QUEUE * evq);
	bool decode();

	void switchPage(ALLEGRO_EVENT ev);


private:
	std::vector<Page> pages;
	unsigned char currentPage;

	allegro_c * alClass;

	std::string dirPath;
	Drawer drawer;

	menuState state = menuState::MAINMENU;
	menuError error = menuError::NO_ERROR;

	bool parserError;
	bool filesystemError;
};

