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
	mainMenu.setImageError(mainMenu.loadImages(&fileReader));						//seteo inicial del programa
	mainMenu.setENCDError(mainMenu.loadENCD(&fileReader));							//y si lo hay, lo carga

	mainMenu.checkError();												//Se fija que errores hubo y cambia el estado y variable de error acorde

	if (!(mainMenu.getError() != menuError::NO_ERROR)) {					//Si hubo algun error
		mainMenu.reportError();											//lo reporto al usuario y cierro programa
		getchar();
	}
	else {

		allegro_c allClass;
		if (allClass.initgood) {
			allClass.load_music(BACKGROUNDMUSIC, 0);
			allClass.load_music(WRONGINPUTSFX, 1);
			allClass.play_music(0);

			mainMenu.loadAllegroClass(&allClass);

			mainMenu.setState(menuState::MAINMENU);							//Sino, comienzo mainmenu, espero que el usuario diga si quiere comprimir
			mainMenu.loopMenu(allClass.getEventQueue());					//o decomprimir. Siempre haciendo un notify() por cada cambio.

			if (mainMenu.getState() == menuState::ENCODER) {
				mainMenu.loopEncoder(allClass.getEventQueue());				//Si quizo comprimir, entro en menu de comprimir
				if (mainMenu.encode()) {									//Comprimo
					mainMenu.setState(menuState::SUCCESS);				//Si fue exitoso
					mainMenu.drawSuccess();										//Notifico exito
				}
				else {
					mainMenu.setState(menuState::ERROR);					//Si hubo error
					mainMenu.drawError();										//Notifico error
				}
			}
			else if (mainMenu.getState() == menuState::DECODER) {			//Si quizo decomprimir, entro en menu de decomprimir
				mainMenu.loopDecoder(allClass.getEventQueue());
				if (mainMenu.decode()) {									//Descomprimo
					mainMenu.setState(menuState::SUCCESS);				//Si fue exitoso
					mainMenu.drawSuccess();										//Notifico exito
				}
				else {
					mainMenu.setState(menuState::ERROR);					//Si hubo error
					mainMenu.drawError();										//Notifico error
				}
			}
		}
	}
	return EXIT_SUCCESS;												//Salgo del programa
}
