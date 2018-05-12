#include "Drawer.h"


	/*No tendr� verificaci�n, ya que solo habr� un observador y se llamar�
	cuando haya que dibujar*/

void Drawer::update(menuState state)
{
	switch (state) {
	case menuState::MAINMENU: drawMenu(); break;
	case menuState::ENCODER: drawEncoder(); break;
	case menuState::DECODER: drawDecoder(); break;
	case menuState::ERROR: drawError(); break;
	case menuState::SUCCESS: drawSuccess(); break;
	}
}

void Drawer::drawMenu() {
}

void Drawer::drawEncoder() {

}

void Drawer::drawDecoder(){}

void Drawer::drawError(){}

void Drawer::drawSuccess(){}

