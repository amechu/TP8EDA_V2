#include "Menu.h"
#include "Parser.h"
#include <iostream>

int main(int argc, char*argv[]) {

	Parser parser;
	Menu mainMenu;

	mainMenu.setParserError(parser.Read(argc, argv));
	mainMenu.setFilesystemError(fileReader.load(parser.getPath()));

	if (mainMenu.getParserError()) {
		
	}
	mainMenu.setState = menuState::MAINMENU;
	return EXIT_SUCCESS;
}