#include "Drawer.h"


	/*No tendrá verificación, ya que solo habrá un observador y se llamará
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
	al_draw_rectangle(0, 0, SCREEN_W, SCREEN_H, al_map_rgb(0, 0, 255),0);
}

void Drawer::drawEncoder() {

}

void Drawer::drawDecoder(){}

void Drawer::drawError(){}

void Drawer::drawSuccess(){}

