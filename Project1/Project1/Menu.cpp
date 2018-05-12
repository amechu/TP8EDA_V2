#include "Menu.h"
#include <iostream>
#include "allegroClass.h"

const int MAXTHRESHOLD = 765;



Menu::Menu()
{
}


Menu::~Menu()
{
}

void const Menu::notify()
{
	drawer.update(this->getState());
}

menuState const Menu::getState()
{
	return this->state;
}

menuError const Menu::getError()
{
	return this->error;
}

void Menu::setParserError(bool error)
{
	parserError = error;
}

bool const Menu::getParserError()
{
	return parserError;
}

void Menu::setFilesystemError(bool error)
{
	filesystemError = error;
}

void Menu::setImageError(bool error)
{
}

void Menu::setENCDError(bool error)
{
}

bool const Menu::getFilesystemError()
{
	return filesystemError;
}

bool Menu::loadImages()
{
	return false;
}

bool Menu::loadENCD()
{
	return false;
}

void Menu::setState(menuState state_)
{
	state = state_;
}

void Menu::setError(menuError error_)
{
	error = error_;
}

void Menu::reportError()
{
	switch (this->getError()) {
	case  menuError::BAD_PARSER:
		std::cout << "ERROR: Invalid parser input. You must input a path and a threshold in the following format: " << std::endl;
		std::cout << "'-path [path name] -threshold [Range: 0 - " << MAXTHRESHOLD << "]'" << std::endl << std::endl;
		std::cout << "'Press any key to end the program and try again." << std::endl;
		break;

	case menuError::BAD_FILEREADER:
		std::cout << "ERROR: The file reader could not find the specified path. " << std::endl << std::endl;
		std::cout << "'Press any key to end the program and try again." << std::endl;
		break;

	case menuError::BAD_IMAGE:
		std::cout << "ERROR: The images could not be loaded. " << std::endl << std::endl;
		std::cout << "'Press any key to end the program and try again." << std::endl;
		break;

	case menuError::BAD_ENCD:
		std::cout << "ERROR: The encoding is corrupted or incorrect. " << std::endl << std::endl;
		std::cout << "'Press any key to end the program and try again." << std::endl;
		break;
	}
}

void Menu::loopMenu(ALLEGRO_EVENT_QUEUE * evq)
{
	ALLEGRO_EVENT alEv;


	this->drawer.update(this->getState());

	while (this->getState() == menuState::MAINMENU) {

		if (al_get_next_event(evq, &alEv)) {

			switch (alEv.type) {

			case ALLEGRO_KEY_DOWN:

				if (alEv.keyboard.keycode == ALLEGRO_KEY_E)
					this->setState(menuState::ENCODER);
				else if (alEv.keyboard.keycode == ALLEGRO_KEY_D)
					this->setState(menuState::DECODER);
				else if (alEv.keyboard.keycode == ALLEGRO_KEY_Q)
					this->setState(menuState::QUIT);

				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				this->setState(menuState::QUIT);
				break;
			}
		}
	}

}

void Menu::loopEncoder(ALLEGRO_EVENT_QUEUE * evq) {


	ALLEGRO_EVENT alEv;

	while (this->getState() == menuState::ENCODER) {


		Image * imPointer = pages[currentPage].getImage(1); //Elijo la primera, pues siempre debería haber, a menos que no haya imagenes a encodear y entonces es NULL.
		bool canSwitchModes = false;

		if (al_get_next_event(evq, &alEv)) {

			switch (alEv.type) {

			case ALLEGRO_KEY_DOWN:
				switch (alEv.keyboard.keycode) {

				case ALLEGRO_KEY_1:	if ((imPointer = pages[currentPage].getImage(1)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_2:	if ((imPointer = pages[currentPage].getImage(2)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_3:	if ((imPointer = pages[currentPage].getImage(3)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_4:	if ((imPointer = pages[currentPage].getImage(4)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_5:	if ((imPointer = pages[currentPage].getImage(5)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_6:	if ((imPointer = pages[currentPage].getImage(6)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_7:	if ((imPointer = pages[currentPage].getImage(7)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_8:	if ((imPointer = pages[currentPage].getImage(8)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_9:	if ((imPointer = pages[currentPage].getImage(9)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;



				case ALLEGRO_KEY_Q: this->setState(menuState::QUIT); break; //Si todo la Q, debo querer salir del programa.

				case ALLEGRO_KEY_ENTER: //Si toco ENTER, procedo a encodear lo que esté seleccionado. Si no hay nada seleccionado, informo a través de un efecto de sonido.
					for (Page page : this->pages)
						for (int i = 0; (imPointer != NULL) && (i < 9) && canSwitchModes == true; i++) {
							if ((imPointer = page.getImage(i)) != NULL) {
								canSwitchModes = (*imPointer).getSelectValue();
							}
						}

					if (canSwitchModes)
						this->setState(menuState::ENCODING);
					else
						this->alClass->play_music(WRONG);

					break;


				case ALLEGRO_KEY_A: //Si toco la A debo poner todo en "seleccionado".

					for (Page page : this->pages)
						for (int i = 0; (imPointer != NULL) && (i < 9); i++) {
							if ((imPointer = page.getImage(i)) != NULL) {
								(*imPointer).toggleSelection(toggleVal::TOGGLETRUE);
							}
						}


				case ALLEGRO_KEY_N: //Si toco la N debo poner todo en "deseleccionado".

					for (Page page : this->pages)
						for (int i = 0; (imPointer != NULL) && (i < 9); i++) {
							if ((imPointer = page.getImage(i)) != NULL) {
								(*imPointer).toggleSelection(toggleVal::TOGGLEFALSE);
							}
						}
					break;

				case ALLEGRO_KEY_LEFT:
				case ALLEGRO_KEY_RIGHT:
					this->switchPage(alEv); //Sea izquierda o derecha, lo trabajo a través de este método.
					break;

				default: alClass->play_music(1); //Efecto de sonido cuando toco una tecla incorrecta
				}
				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				this->setState(menuState::QUIT);
				break;
			}
		}
	}
}

bool Menu::encode()
{
	return false;
}

void Menu::loopDecoder(ALLEGRO_EVENT_QUEUE * evq)
{
	ALLEGRO_EVENT alEv;


	while (this->getState() == menuState::DECODER) {


		Image * imPointer = pages[currentPage].getImage(1); //Elijo la primera, pues siempre debería haber, a menos que no haya imagenes a encodear y entonces es NULL.
		bool canSwitchModes = false;

		if (al_get_next_event(evq, &alEv)) {

			switch (alEv.type) {

			case ALLEGRO_KEY_DOWN:
				switch (alEv.keyboard.keycode) {

				case ALLEGRO_KEY_1:	if ((imPointer = pages[currentPage].getImage(1)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_2:	if ((imPointer = pages[currentPage].getImage(2)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_3:	if ((imPointer = pages[currentPage].getImage(3)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_4:	if ((imPointer = pages[currentPage].getImage(4)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_5:	if ((imPointer = pages[currentPage].getImage(5)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_6:	if ((imPointer = pages[currentPage].getImage(6)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_7:	if ((imPointer = pages[currentPage].getImage(7)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_8:	if ((imPointer = pages[currentPage].getImage(8)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;
				case ALLEGRO_KEY_9:	if ((imPointer = pages[currentPage].getImage(9)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); }	break;



				case ALLEGRO_KEY_Q: this->setState(menuState::QUIT); break; //Si todo la Q, debo querer salir del programa.

				case ALLEGRO_KEY_ENTER: //Si toco ENTER, procedo a decodear lo que esté seleccionado. Si no hay nada seleccionado, informo a través de un efecto de sonido.
					for (Page page : this->pages)
						for (int i = 0; (imPointer != NULL) && (i < 9) && canSwitchModes == true; i++) {
							if ((imPointer = page.getImage(i)) != NULL) {
								canSwitchModes = (*imPointer).getSelectValue();
							}
						}

					if (canSwitchModes)
						this->setState(menuState::DECODING);
					else
						this->alClass->play_music(WRONG);
					
					break; 


				case ALLEGRO_KEY_A: //Si toco la A debo poner todo en "seleccionado".

					for (Page page : this->pages)
						for (int i = 0; (imPointer != NULL) && (i < 9); i++) {
							if ((imPointer = page.getImage(i)) != NULL) {
								(*imPointer).toggleSelection(toggleVal::TOGGLETRUE);
							}
						}


				case ALLEGRO_KEY_N: //Si toco la N debo poner todo en "deseleccionado".

					for (Page page : this->pages)
						for (int i = 0; (imPointer != NULL) && (i < 9); i++) {
							if ((imPointer = page.getImage(i)) != NULL) {
								(*imPointer).toggleSelection(toggleVal::TOGGLEFALSE);
							}
						}
					break;

				case ALLEGRO_KEY_LEFT:
				case ALLEGRO_KEY_RIGHT:
					this->switchPage(alEv); //Sea izquierda o derecha, lo trabajo a través de este método.
					break;

				default: alClass->play_music(1); //Efecto de sonido cuando toco una tecla incorrecta
				}
				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				this->setState(menuState::QUIT);
				break;
			}
		}
	}
}

bool Menu::decode()
{
	return false;
}

void Menu::switchPage(ALLEGRO_EVENT ev)
{
	if (ev.type == ALLEGRO_KEY_LEFT) {
		if (this->currentPage == 1) { //Si es la primera página, no puedo descender más.
			this->alClass->play_music(WRONG);
		}
		else {
			currentPage--; //Si no es la pagina 1, puedo descender.
		}
	}
	if (ev.type == ALLEGRO_KEY_RIGHT) {
		if (this->pages.size() == currentPage) { //Si estoy en la última página, no puedo ascender más.
			this->alClass->play_music(WRONG);
		}
		else {
			currentPage++; //Si no es la página final, puedo ascender.
		}
	}
}

void Menu::checkError()
{
	if (getFilesystemError()) {
		setError(menuError::BAD_FILEREADER);
	}
	if (getParserError()) {
		setError(menuError::BAD_PARSER);
	}
}

void Menu::loadAllegroClass(allegro_c * alClass_) {
	this->alClass = alClass_;
}