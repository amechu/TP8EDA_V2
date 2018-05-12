#pragma once

#include "allegroClass.h"
enum class menuState { MAINMENU, ENCODER, DECODER, ENCODING, DECODING, SUCCESS, ERROR, QUIT };

class Drawer {
public:

	void update(menuState state);

private:

	void drawMenu();
	void drawEncoder();
	void drawDecoder();
	void drawError();
	void drawSuccess();

};