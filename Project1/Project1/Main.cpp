#include "Menu.h"
#include "allegroClass.h"
#include "Parser.h"
#include "FileReader.h"
#include <iostream>

int main(int argc, char*argv[]) {

	Parser parser;
	Menu mainMenu;
	FileReader fileReader;

	mainMenu.setParserError(parser.Read(argc, argv));					//Se fija si hubo
	mainMenu.setFilesystemError(fileReader.load(parser.getPath()));		//algun error a lo largo del
	mainMenu.setImageError(mainMenu.loadImages());						//seteo inicial del programa
	mainMenu.setENCDError(mainMenu.loadENCD());							//y si lo hay, lo carga

	mainMenu.checkError();												//Se fija que errores hubo y cambia el estado y variable de error acorde

	if (mainMenu.getError() != menuError::NO_ERROR) {					//Si hubo algun error
		mainMenu.reportError();											//lo reporto al usuario y cierro programa
	}
	else {

		allegro_c allClass;
		allClass.load_music(BACKGROUNDMUSIC);
		allClass.play_music();

		mainMenu.setState(menuState::MAINMENU);							//Sino, comienzo mainmenu, espero que el usuario diga si quiere comprimir
		mainMenu.loopMenu();											//o decomprimir. Siempre haciendo un notify() por cada cambio.
		if (mainMenu.getState() == menuState::ENCODER) {
			mainMenu.loopEncoder();										//Si quizo comprimir, entro en menu de comprimir
			if (mainMenu.encode()) {									//Comprimo
				mainMenu.setState(menuState::SUCCESS);				//Si fue exitoso
				mainMenu.notify();										//Notifico exito
			}
			else {
				mainMenu.setState(menuState::ERROR);					//Si hubo error
				mainMenu.notify();										//Notifico error
			}
		}
		else if (mainMenu.getState() == menuState::DECODER) {			//Si quizo decomprimir, entro en menu de decomprimir
			mainMenu.loopDecoder();										
			if (mainMenu.decode()) {									//Decomprimo
				mainMenu.setState(menuState::SUCCESS);				//Si fue exitoso
				mainMenu.notify();										//Notifico exito
			}
			else {
				mainMenu.setState(menuState::ERROR);					//Si hubo error
				mainMenu.notify();										//Notifico error
			}
		}
		getchar();
	}
		
	return EXIT_SUCCESS;												//Salgo del programa
}