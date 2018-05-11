#pragma once

#include "Page.h"
#include "Drawer.h"
#include <vector>

enum class menuState { MAINMENU, ENCODER, DECODER, SUCCESS };

class Menu
{
public:
	Menu();
	~Menu();

private:
	std::vector<Page> pages;
	std::string dirPath;
	Drawer drawer;
	menuState state;
};

