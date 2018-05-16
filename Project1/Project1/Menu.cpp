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
				imgpages[pagecounter - 1]->addImage(lastPath);
		}
		else {
			if (counter < 10) {

				imgpages[pagecounter - 1]->addImage(path);

				if (imgpages[pagecounter - 1]->images[counter - 1]->error)
					error = true;
				counter++;
			}
			else {
				addPage(pagecounter + 1);
				pagecounter++;
				counter = 1;
				imgpages[pagecounter - 1]->addImage(path);
				if (imgpages[pagecounter - 1]->images[counter - 1]->error)
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
			encdpages[pagecounter -1]->addENCD(path);
			if (encdpages[pagecounter -1]->encdfiles[counter - 1]->error)
				error = true;
			counter++;
		}
		else {
			addPageENCD(pagecounter + 1);
			pagecounter++;
			counter = 1;
			encdpages[pagecounter -1]->addENCD(path);
			if (encdpages[pagecounter -1]->encdfiles[counter - 1]->error)
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

		if (this->imgpages.size() > 0) //Si hay almenos una página, hago que imPointer apunte a esa página. Si no la hay, permanece en NULL. IMPORTANTE PARA LOS FOR.
			imPointer = imgpages[currentPage-1]->getImage(1);

		bool canSwitchModes = false;

		if (al_get_next_event(evq, &alEv)) {

			switch (alEv.type) {

			case ALLEGRO_EVENT_KEY_DOWN:
				switch (alEv.keyboard.keycode) {

				case ALLEGRO_KEY_1:	if ((imPointer = imgpages[currentPage-1]->getImage(1)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_2:	if ((imPointer = imgpages[currentPage-1]->getImage(2)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_3:	if ((imPointer = imgpages[currentPage-1]->getImage(3)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_4:	if ((imPointer = imgpages[currentPage-1]->getImage(4)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_5:	if ((imPointer = imgpages[currentPage-1]->getImage(5)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_6:	if ((imPointer = imgpages[currentPage-1]->getImage(6)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_7:	if ((imPointer = imgpages[currentPage-1]->getImage(7)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_8:	if ((imPointer = imgpages[currentPage-1]->getImage(8)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_9:	if ((imPointer = imgpages[currentPage-1]->getImage(9)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;


				case ALLEGRO_KEY_ESCAPE:
				case ALLEGRO_KEY_Q: this->setState(menuState::QUIT); break; //Si todo la Q, debo querer salir del programa.

				case ALLEGRO_KEY_ENTER: //Si toco ENTER, procedo a encodear lo que esté seleccionado. Si no hay nada seleccionado, informo a través de un efecto de sonido.
					for (Page* page : this->imgpages)
						for (int i = 0; (imPointer != NULL) && (i < 9) && canSwitchModes == false; i++) { //Si aun no llegué a un puntero a NULL (Que implica que los siguientes también lo son) y aun no encontré almenos una imagen seleccionada
							if ((imPointer = page->getImage(i+1)) != NULL) { //...Sigo loopeando hasta encontrar una seleccionada o llegar al final de la lista.
								canSwitchModes = (*imPointer).getSelectValue();
							}
						}

					if (canSwitchModes) { //Si había almenos una imagen seleccionada, procedo a cambiar el estado y a redibujar el menu.
						this->setState(menuState::ENCODING);
					}
					else
						this->alClass->play_music(WRONG); // WRONG.

					break;


				case ALLEGRO_KEY_A: //Si toco la A debo poner todo en "seleccionado".

					for (Page* page : this->imgpages)
						for (int i = 0; (imPointer != NULL) && (i < 9); i++) {
							if ((imPointer = page->getImage(i+1)) != NULL) {
								(*imPointer).toggleSelection(toggleVal::TOGGLETRUE);
							}
						}

					this->shouldRedraw = true;
					break;

				case ALLEGRO_KEY_N: //Si toco la N debo poner todo en "deseleccionado".

					for (Page* page : this->imgpages)
						for (int i = 0; (imPointer != NULL) && (i < 9); i++) {
							if ((imPointer = page->getImage(i+1)) != NULL) {
								(*imPointer).toggleSelection(toggleVal::TOGGLEFALSE);
							}
						}
					this->shouldRedraw = true;
					break;

				case ALLEGRO_KEY_LEFT:
					if (this->currentPage > 1) {
						this->imgpages[currentPage-1]->setSelected(false);
						currentPage--;
						this->imgpages[currentPage-1]->setSelected(true);
						shouldRedraw = true;
					}
					break;
				case ALLEGRO_KEY_RIGHT:
					if (this->currentPage < this->imgpages.size()) {
						this->imgpages[currentPage-1]->setSelected(false);
						currentPage++;
						this->imgpages[currentPage-1]->setSelected(true);
						shouldRedraw = true;
					}
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
	std::vector<Image*> toEncode;
	Image* img;
	std::string encoded;

	for (Page* page : imgpages) {
		for (Image* img : page->images) {
			if (img != nullptr && img->getSelectValue())
				toEncode.push_back(img);
		}
	}

	while (!toEncode.empty()) {

		img = toEncode.back();
		toEncode.pop_back();

		encoded += quadtree(img->pixels, img->getWidth());

		//save(encoded);
	}
	return false;
}

std::string Menu::quadtree(std::vector<unsigned char> pixels, unsigned side)
{
	std::vector<unsigned char> firstquarter, secondquarter, thirdquarter, fourthquarter;
	std::string returnVal;
	unsigned puntaje = 0, Mr = 0, mr = 255, Mg = 0, mg = 255, Mb = 0, mb = 255;
	unsigned char promedio=0;

	//Si llegue aca, es porque branchie.
	returnVal += 'B';

	for (int i = 0; i < side / 4; i++) { //Calculo maximos y minimos
		if (pixels[i] > Mr)
			Mr = pixels[i];
		if (pixels[i] < mr)
			mr = pixels[i];
		if (pixels[i + 1] > Mg)
			Mg = pixels[i + 1];
		if (pixels[i + 1] < mg)
			mg = pixels[i + 1];
		if (pixels[i + 2] > Mb)
			Mb = pixels[i + 2];
		if (pixels[i + 2] < mb)
			mb = pixels[i + 2];
	}
	puntaje = Mr - mr + Mg - mg + Mb - mb;

	if (puntaje < this->threshold) {
		//No tengo que branchear mas
		returnVal += 'N';
		//Calculo promedio
		Mr = Mg = Mb = 0;
		for (int j = 0; j < side / 4; j++) {
			Mr += pixels[j];
			Mg += pixels[j + 1];
			Mb += pixels[j + 2];
		}
		Mr /= side / 4;
		Mg /= side / 4;
		Mb /= side / 4;
		//Meto el color de la subimagen al string
		returnVal += Mr;
		returnVal += Mg;
		returnVal += Mb;
		return returnVal;
	}

	else {
		//Tengo que partir imagen en 4 sub-cuadrados.
		for (int y1 = 0; y1 < side / 2; y1++) { //Primera mitad en altura
			for (int x1 = 0; x1 < side / 2; x1++) { //Primera mitad en anchura
				firstquarter.push_back(pixels[x1 + (y1*(side / 2))]); //Capturo linea horizontal de largo side/2 y al llegar al final se sumo una linea de largo side/2 (los de la segunda mitad en anchura)
				secondquarter.push_back(pixels[((side / 2)*y1) + x1]); //Misma idea, pero primero sumo side/2
			}
		}
		for (int y2 = side/2; y2 < side; y2++) { //Segunda mitad en altura
			for (int x1 = 0; x1 < side / 2; x1++) { //Primera mitad en anchura
				thirdquarter.push_back(pixels[x1 + (y2*(side / 2))]); //Misma idea pero sumo la mitad de la imagen primero
				fourthquarter.push_back(pixels[((side / 2) + y2) + x1]);
			}
		}

		returnVal += quadtree(firstquarter, side / 2); //Llamadas recursivas con un largo de lado mitad que el anterior.
		returnVal += quadtree(secondquarter, side / 2);
		returnVal += quadtree(thirdquarter, side / 2);
		returnVal += quadtree(fourthquarter, side / 2);

		return returnVal;
	}
}

void Menu::loopDecoder(ALLEGRO_EVENT_QUEUE * evq)
{
	ALLEGRO_EVENT alEv;

	this->drawer.drawDecoder(&(this->encdpages));

	while (this->getState() == menuState::DECODER) {

		ENCD_FILE * imPointer = NULL;

		if (this->encdpages.size() > 0) //Si hay almenos una página, hago que imPointer apunte a esa página. Si no la hay, permanece en NULL. IMPORTANTE PARA LOS FOR.
			imPointer = encdpages[currentPage-1]->getENCD(1);

		bool canSwitchModes = false; //Booleano que me indica si puedo 

		if (al_get_next_event(evq, &alEv)) {

			switch (alEv.type) {

			case ALLEGRO_EVENT_KEY_DOWN:
				switch (alEv.keyboard.keycode) {

				case ALLEGRO_KEY_1:	if ((imPointer = encdpages[currentPage-1]->getENCD(1)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break; //Si toco un número, debo cambiar el valor de selección
				case ALLEGRO_KEY_2:	if ((imPointer = encdpages[currentPage - 1]->getENCD(2)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break; //de la imagen en pantalla a la cual corresponde ese número.
				case ALLEGRO_KEY_3:	if ((imPointer = encdpages[currentPage - 1]->getENCD(3)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_4:	if ((imPointer = encdpages[currentPage - 1]->getENCD(4)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_5:	if ((imPointer = encdpages[currentPage - 1]->getENCD(5)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_6:	if ((imPointer = encdpages[currentPage - 1]->getENCD(6)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_7:	if ((imPointer = encdpages[currentPage - 1]->getENCD(7)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_8:	if ((imPointer = encdpages[currentPage - 1]->getENCD(8)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;
				case ALLEGRO_KEY_9:	if ((imPointer = encdpages[currentPage - 1]->getENCD(9)) != NULL) { (*imPointer).toggleSelection(toggleVal::TOGGLE); this->shouldRedraw = true; }	break;


				case ALLEGRO_KEY_ESCAPE:
				case ALLEGRO_KEY_Q: this->setState(menuState::QUIT); break; //Si todo la Q, debo querer salir del programa.

				case ALLEGRO_KEY_ENTER: //Si toco ENTER, procedo a decodear lo que esté seleccionado. Si no hay nada seleccionado, informo a través de un efecto de sonido.
					for (ENCDPage* page : this->encdpages)
						for (int i = 0; (imPointer != NULL) && (i < 9) && canSwitchModes == false; i++) { //Si no llegué a un NULL pointer (o sea que aún podría haber imagenes seleccionadas) y aún no encontré una seleccionada....
							if ((imPointer = page->getENCD(i+1)) != NULL) { //...Sigo buscando hasta encontrar una seleccionada.
								canSwitchModes = (*imPointer).getSelectValue();
							}
						}

					if (canSwitchModes) {
						this->setState(menuState::DECODING); //Si encontré almenos una seleccionada, procedo al codeo.
						this->shouldRedraw = true;
					}
					else
						this->alClass->play_music(WRONG); // De lo contrario, como diría Donald Trump: WRONG.

					break;


				case ALLEGRO_KEY_A: //Si toco la A debo poner todo en "seleccionado".

					for (ENCDPage* page : this->encdpages)
						for (int i = 0; (imPointer != NULL) && (i < 9); i++) {
							if ((imPointer = page->getENCD(i+1)) != NULL) {
								(*imPointer).toggleSelection(toggleVal::TOGGLETRUE);
							}
						}

					this->shouldRedraw = true;
					break;

				case ALLEGRO_KEY_N: //Si toco la N debo poner todo en "deseleccionado".

					for (ENCDPage* page : this->encdpages)
						for (int i = 0; (imPointer != NULL) && (i < 9); i++) {
							if ((imPointer = page->getENCD(i+1)) != NULL) {
								(*imPointer).toggleSelection(toggleVal::TOGGLEFALSE);
							}
						}

					this->shouldRedraw = true;
					break;

				case ALLEGRO_KEY_LEFT:
					if (this->currentPage > 1) {
						this->encdpages[currentPage - 1]->setSelected(false);
						currentPage--;
						this->encdpages[currentPage - 1]->setSelected(true);
						shouldRedraw = true;
					}
					break;
				case ALLEGRO_KEY_RIGHT:
					if (this->currentPage < this->encdpages.size()) {
						this->encdpages[currentPage - 1]->setSelected(false);
						currentPage++;
						this->encdpages[currentPage - 1]->setSelected(true);
						shouldRedraw = true;
					}
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
		if (this->currentPage == 1) { //Si es la primera página, no puedo descender más.
			this->alClass->play_music(WRONG);
		}
		else {
			currentPage--; //Si no es la pagina 1, puedo descender.
		}
	}
	if (ev.type == ALLEGRO_KEY_RIGHT) {
		if (this->imgpages.size() == currentPage) { //Si estoy en la última página, no puedo ascender más.
			this->alClass->play_music(WRONG);
		}
		else {
			currentPage++; //Si no es la página final, puedo ascender.
		}
	}
}

void Menu::switchPageENCD(ALLEGRO_EVENT ev)
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
		if (this->imgpages.size() == currentPage) { //Si estoy en la última página, no puedo ascender más.
			this->alClass->play_music(WRONG);
		}
		else {
			currentPage++; //Si no es la página final, puedo ascender.
		}
	}
}

void Menu::addPage(unsigned pageNum)
{
	Page* page = new Page(pageNum);
	imgpages.push_back(page);
}
void Menu::addPageENCD(unsigned pageNum)
{
	encdpages.push_back((new ENCDPage(pageNum)));
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