#include "Menu.h"
#include <iostream>
#include "allegroClass.h"

const int MAXTHRESHOLD = 765;

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

bool const Menu::getFilesystemError()
{
	return filesystemError;
}

void Menu::setImageError(bool error)
{
	this->imageError = error;
}

bool const Menu::getENCDError()
{
	return ENCDerror;
}

void Menu::setENCDError(bool error)
{
	this->ENCDerror = true;
}

bool const Menu::getImageError()
{
	return imageError;
}

bool Menu::loadImages(FileReader* FR)
{
	unsigned counter = 1;
	unsigned pagecounter = 0;
	bool error = false;
	bool atLeastOnePNG = false;

	if (this->imgpages.size() == 0) {
		addPage(pagecounter + 1);
		pagecounter++;
	}

	std::string lastPath = "";

	for (std::string path : FR->pngpaths) {

		lastPath = path;

		if (lastPath == "") {
			for (; counter != 10; counter++)
				imgpages[pagecounter - 1].addImage(lastPath);
		}
		else {
			if (counter < 10) {

				imgpages[pagecounter - 1].addImage(path);

				if (imgpages[pagecounter - 1].images[counter - 1]->error)
					error = true;
				counter++;
			}
			else {
				addPage(pagecounter + 1);
				pagecounter++;
				counter = 1;
				imgpages[pagecounter - 1].addImage(path);
				if (imgpages[pagecounter - 1].images[counter - 1]->error)
					error = true;
				counter++;
			}

		}

	}

	return error;
}

bool Menu::loadENCD(FileReader* FR)
{
	unsigned counter = 1;
	unsigned pagecounter = 0;
	bool error = false;

	if (this->encdpages.size() == 0) {
		addPageENCD(pagecounter + 1);
		pagecounter++;
	}

	for (std::string path : FR->ENCDpaths) {
		if (counter < 10) {
			encdpages[pagecounter - 1].addENCD(path);
			if (encdpages[pagecounter - 1].encdfiles[counter - 1]->error)
				error = true;
			counter++;
		}
		else {
			addPage(pagecounter + 1);
			pagecounter++;
			counter = 1;
			encdpages[pagecounter - 1].addENCD(path);
			if (encdpages[pagecounter - 1].encdfiles[counter - 1]->error)
				error = true;
			counter++;
		}
	}
	return error;
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

	this->drawer.drawMenu();

	while (this->getState() == menuState::MAINMENU) {

		if (al_get_next_event(evq, &alEv)) {

			switch (alEv.type) {

			case ALLEGRO_EVENT_KEY_DOWN:

				if (alEv.keyboard.keycode == ALLEGRO_KEY_E)
					this->setState(menuState::ENCODER);
				else if (alEv.keyboard.keycode == ALLEGRO_KEY_D)
					this->setState(menuState::DECODER);
				else if (alEv.keyboard.keycode == ALLEGRO_KEY_Q || alEv.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
					this->setState(menuState::QUIT);
				else
					this->alClass->play_music(WRONG);

				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				this->setState(menuState::QUIT);
				break;
			}
		}
	}

}

void Menu::loopEncoder(ALLEGRO_EVENT_QUEUE * evq) {

	this->drawer.drawEncoder(&(this->imgpages));

	ALLEGRO_EVENT alEv;

	while (this->getState() == menuState::ENCODER) {

		Image * imPointer = NULL;

		if (this->imgpages.size() > 0) //Si hay almenos una p�gina, hago que imPointer apunte a esa p�gina. Si no la hay, permanece en NULL. IMPORTANTE PARA LOS FOR.
			imPointer = imgpages[currentPage].getImage(1);

		bool canSwitchModes = false;

		if (al_get_next_event(evq, &alEv)) {

			switch (alEv.type) {

			case ALLEGRO_EVENT_KEY_DOWN:
				switch (alEv.keyboard.keycode) {

				case ALLEGRO_KEY_1:	if ((imPointer = imgpages[currentPage].getImage(1)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_2:	if ((imPointer = imgpages[currentPage].getImage(2)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_3:	if ((imPointer = imgpages[currentPage].getImage(3)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_4:	if ((imPointer = imgpages[currentPage].getImage(4)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_5:	if ((imPointer = imgpages[currentPage].getImage(5)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_6:	if ((imPointer = imgpages[currentPage].getImage(6)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_7:	if ((imPointer = imgpages[currentPage].getImage(7)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_8:	if ((imPointer = imgpages[currentPage].getImage(8)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_9:	if ((imPointer = imgpages[currentPage].getImage(9)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;



				case ALLEGRO_KEY_Q: this->setState(menuState::QUIT); break; //Si todo la Q, debo querer salir del programa.

				case ALLEGRO_KEY_ENTER: //Si toco ENTER, procedo a encodear lo que est� seleccionado. Si no hay nada seleccionado, informo a trav�s de un efecto de sonido.
					for (Page page : this->imgpages)
						for (int i = 0; (imPointer != NULL) && (i < 9) && canSwitchModes == false; i++) { //Si aun no llegu� a un puntero a NULL (Que implica que los siguientes tambi�n lo son) y aun no encontr� almenos una imagen seleccionada
							if ((imPointer = page.getImage(i)) != NULL) { //...Sigo loopeando hasta encontrar una seleccionada o llegar al final de la lista.
								canSwitchModes = (*imPointer).getSelectValue();
							}
						}

					if (canSwitchModes) { //Si hab�a almenos una imagen seleccionada, procedo a cambiar el estado y a redibujar el menu.
						this->setState(menuState::ENCODING);
						this->shouldRedraw = true;
					}
					else
						this->alClass->play_music(WRONG); // WRONG.

					break;


				case ALLEGRO_KEY_A: //Si toco la A debo poner todo en "seleccionado".

					for (Page page : this->imgpages)
						for (int i = 0; (imPointer != NULL) && (i < 9); i++) {
							if ((imPointer = page.getImage(i)) != NULL) {
								(*imPointer).toggleSelection(toggleVal::TOGGLETRUE);
							}
						}

					this->shouldRedraw = true;
					break;

				case ALLEGRO_KEY_N: //Si toco la N debo poner todo en "deseleccionado".

					for (Page page : this->imgpages)
						for (int i = 0; (imPointer != NULL) && (i < 9); i++) {
							if ((imPointer = page.getImage(i)) != NULL) {
								(*imPointer).toggleSelection(toggleVal::TOGGLEFALSE);
							}
						}
					this->shouldRedraw = true;
					break;

				case ALLEGRO_KEY_LEFT:
				case ALLEGRO_KEY_RIGHT:
					this->switchPage(alEv); //Sea izquierda o derecha, lo trabajo a trav�s de este m�todo.
					this->shouldRedraw = true;
					break;

				default: alClass->play_music(WRONG); //Efecto de sonido cuando toco una tecla incorrecta
				}
				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				this->setState(menuState::QUIT);
				break;
			}
		}
		if (this->shouldRedraw) {
			this->drawer.drawEncoder(&(this->imgpages));
			this->shouldRedraw = false;
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

	this->drawer.drawDecoder(&(this->encdpages));

	while (this->getState() == menuState::DECODER) {

		ENCD_FILE * imPointer = NULL;

		if (this->encdpages.size() > 0) //Si hay almenos una p�gina, hago que imPointer apunte a esa p�gina. Si no la hay, permanece en NULL. IMPORTANTE PARA LOS FOR.
			imPointer = encdpages[currentPage].getENCD(1);

		bool canSwitchModes = false; //Booleano que me indica si puedo 

		if (al_get_next_event(evq, &alEv)) {

			switch (alEv.type) {

			case ALLEGRO_EVENT_KEY_DOWN:
				switch (alEv.keyboard.keycode) {

				case ALLEGRO_KEY_1:	if ((imPointer = encdpages[currentPage].getENCD(1)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break; //Si toco un n�mero, debo cambiar el valor de selecci�n
				case ALLEGRO_KEY_2:	if ((imPointer = encdpages[currentPage].getENCD(2)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break; //de la imagen en pantalla a la cual corresponde ese n�mero.
				case ALLEGRO_KEY_3:	if ((imPointer = encdpages[currentPage].getENCD(3)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_4:	if ((imPointer = encdpages[currentPage].getENCD(4)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_5:	if ((imPointer = encdpages[currentPage].getENCD(5)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_6:	if ((imPointer = encdpages[currentPage].getENCD(6)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_7:	if ((imPointer = encdpages[currentPage].getENCD(7)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_8:	if ((imPointer = encdpages[currentPage].getENCD(8)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_9:	if ((imPointer = encdpages[currentPage].getENCD(9)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;



				case ALLEGRO_KEY_Q: this->setState(menuState::QUIT); break; //Si todo la Q, debo querer salir del programa.

				case ALLEGRO_KEY_ENTER: //Si toco ENTER, procedo a decodear lo que est� seleccionado. Si no hay nada seleccionado, informo a trav�s de un efecto de sonido.
					for (ENCDPage page : this->encdpages)
						for (int i = 0; (imPointer != NULL) && (i < 9) && canSwitchModes == false; i++) { //Si no llegu� a un NULL pointer (o sea que a�n podr�a haber imagenes seleccionadas) y a�n no encontr� una seleccionada....
							if ((imPointer = page.getENCD(i)) != NULL) { //...Sigo buscando hasta encontrar una seleccionada.
								canSwitchModes = (*imPointer).getSelectValue();
							}
						}

					if (canSwitchModes) {
						this->setState(menuState::DECODING); //Si encontr� almenos una seleccionada, procedo al codeo.
						this->shouldRedraw = true;
					}
					else
						this->alClass->play_music(WRONG); // De lo contrario, como dir�a Donald Trump: WRONG.

					break;


				case ALLEGRO_KEY_A: //Si toco la A debo poner todo en "seleccionado".

					for (ENCDPage page : this->encdpages)
						for (int i = 0; (imPointer != NULL) && (i < 9); i++) {
							if ((imPointer = page.getENCD(i)) != NULL) {
								(*imPointer).toggleSelection(toggleVal::TOGGLETRUE);
							}
						}

					this->shouldRedraw = true;
					break;

				case ALLEGRO_KEY_N: //Si toco la N debo poner todo en "deseleccionado".

					for (ENCDPage page : this->encdpages)
						for (int i = 0; (imPointer != NULL) && (i < 9); i++) {
							if ((imPointer = page.getENCD(i)) != NULL) {
								(*imPointer).toggleSelection(toggleVal::TOGGLEFALSE);
							}
						}

					this->shouldRedraw = true;
					break;

				case ALLEGRO_KEY_LEFT:
				case ALLEGRO_KEY_RIGHT:
					this->switchPage(alEv); //Sea izquierda o derecha, lo trabajo a trav�s de este m�todo.
					this->shouldRedraw = true;
					break;

				default: alClass->play_music(WRONG); //Efecto de sonido cuando toco una tecla incorrecta
				}
				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				this->setState(menuState::QUIT);
				break;
			}
		}
		if (this->shouldRedraw) {
			this->drawer.drawDecoder(&(this->encdpages));
			this->shouldRedraw = false;
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
		if (this->currentPage == 1) { //Si es la primera p�gina, no puedo descender m�s.
			this->alClass->play_music(WRONG);
		}
		else {
			currentPage--; //Si no es la pagina 1, puedo descender.
		}
	}
	if (ev.type == ALLEGRO_KEY_RIGHT) {
		if (this->imgpages.size() == currentPage) { //Si estoy en la �ltima p�gina, no puedo ascender m�s.
			this->alClass->play_music(WRONG);
		}
		else {
			currentPage++; //Si no es la p�gina final, puedo ascender.
		}
	}
}

void Menu::switchPageENCD(ALLEGRO_EVENT ev)
{
	if (ev.type == ALLEGRO_KEY_LEFT) {
		if (this->currentPage == 1) { //Si es la primera p�gina, no puedo descender m�s.
			this->alClass->play_music(WRONG);
		}
		else {
			currentPage--; //Si no es la pagina 1, puedo descender.
		}
	}
	if (ev.type == ALLEGRO_KEY_RIGHT) {
		if (this->imgpages.size() == currentPage) { //Si estoy en la �ltima p�gina, no puedo ascender m�s.
			this->alClass->play_music(WRONG);
		}
		else {
			currentPage++; //Si no es la p�gina final, puedo ascender.
		}
	}
}

void Menu::addPage(unsigned pageNum)
{
	Page* page = new Page(pageNum);
	imgpages.push_back(*page);
}
void Menu::addPageENCD(unsigned pageNum)
{
	encdpages.push_back(*(new ENCDPage(pageNum)));
}

void Menu::checkError()
{
	if (getFilesystemError()) {
		setError(menuError::BAD_FILEREADER);
		this->reportError();
	}
	else if (getParserError()) {
		setError(menuError::BAD_PARSER);
		this->reportError();
	}
	else if (getImageError()) {
		setError(menuError::BAD_IMAGE);
		this->reportError();
	}
	else if (getParserError()) {
		setError(menuError::BAD_ENCD);
		this->reportError();
	}
}

void Menu::loadAllegroClass(allegro_c * alClass_) {
	this->alClass = alClass_;
	this->drawer.getDrawTool(alClass_);
}