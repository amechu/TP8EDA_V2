#include "Menu.h"
#include "Parser.h"
#include <iostream>

int main(int argc, char*argv[]) {

	Parser parser;
	Menu mainMenu;

	mainMenu.setParserError(parser.Read(argc, argv));
	mainMenu.setFilesystemError(fileReader.load(parser.getPath()));
	mainMenu.setImageError(mainMenu.loadImages());
	mainMenu.setENCDError(mainMenu.loadENCD());

	mainMenu.checkError();

	if (mainMenu.getError() != menuError::NO_ERROR) {
		mainMenu.reportError();
	}
	else {
		mainMenu.setState(menuState::MAINMENU);
		mainMenu.loopMenu();
		if (mainMenu.getState() == menuState::ENCODER) {
			mainMenu.notify();
			if (mainMenu.encodeSelected()) {
				mainMenu.setState == menuState::SUCCESS;
				mainMenu.notify();
			}
			else {
				mainMenu.setState == menuState::ERROR;
				mainMenu.notify();
			}
		}
		else if (mainMenu.getState() == menuState::DECODER) {
			if (mainMenu.decodeSelected()) {
				mainMenu.setState == menuState::SUCCESS;
				mainMenu.notify();
			}
			else {
				mainMenu.setState == menuState::ERROR;
				mainMenu.notify();
			}
		}
	}

	return EXIT_SUCCESS;
}