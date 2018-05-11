#include "Menu.h"
#include "allegroClass.h"
#include "Parser.h"
#include <iostream>

int main(int argc, char*argv[]) {

	Parser parser;
	Menu mainMenu;


	mainMenu.setParserError(parser.Read(argc, argv));
	mainMenu.setFilesystemError(fileReader.load(parser.getPath()));

	if (mainMenu.getParserError()) {

		allegro_c allClass;
		allClass.load_music(BACKGROUNDMUSIC);
		allClass.play_music();

		getchar();

	}

	mainMenu.setState = menuState::MAINMENU;

	

	return EXIT_SUCCESS;
}