#pragma once

class allegro_c;

#include "Page.h"
#include "Drawer.h"
#include "FileReader.h"
#include "ENCDPage.h"
#include <vector>
#include <iostream>
#include <fstream>

enum class menuError { BAD_PARSER, BAD_FILEREADER, BAD_IMAGE, BAD_ENCD , NO_ERROR};


class Menu {
public:
	Menu() {}
	~Menu() {}

	bool const getParserError();
	bool const getImageError();
	bool const getENCDError();
	bool const getFilesystemError();
	bool loadImages(FileReader* FR);
	bool loadENCD(FileReader* FR);

	menuState const getState();
	menuError const getError();

	void setParserError(bool error);
	void setFilesystemError(bool error);
	void setImageError(bool error);
	void setENCDError(bool error);
	void setState(menuState state_);
	void setError(menuError error_);
	void getThreshold(unsigned threshold_) { threshold = threshold_; }
	void loadAllegroClass(allegro_c * alClass_);

	void checkError();
	void reportError();
	void loopMenu(ALLEGRO_EVENT_QUEUE * evq);
	void loopEncoder(ALLEGRO_EVENT_QUEUE * evq);
	bool encode();
	void save(std::string encoded, std::string filename);
	void loadingScreen();
	std::string quadtree(std::vector<unsigned char> pixels, unsigned side);
	void loopDecoder(ALLEGRO_EVENT_QUEUE * evq);
	bool decode();

	void encdDecoder(std::ifstream&  encdfile,int length,unsigned char * rawpixels, int x, int y, int size );
	void colorear(std::ifstream& encdfile, int length, unsigned char * rawpixels, unsigned char colores[4], int x, int y, int size);

	void drawSuccess() { drawer.drawSuccess(); }
	void drawError() { drawer.drawError(); }

	void switchPage(ALLEGRO_EVENT ev);
	void switchPageENCD(ALLEGRO_EVENT ev);

	void addPage(unsigned pageNum);
	void addPageENCD(unsigned pageNum);

private:
	std::vector<Page*> imgpages;
	std::vector<ENCDPage*> encdpages;
	unsigned char currentPage = 1;
	unsigned threshold;

	allegro_c * alClass;

	std::string dirPath;
	Drawer drawer;

	menuState state = menuState::MAINMENU;
	menuError error = menuError::NO_ERROR;

	bool parserError;
	bool filesystemError;
	bool imageError;
	bool ENCDerror;

	bool shouldRedraw; //Variable utilizada para saber si debo, o no, llamar a update del drawer.
};

