#pragma once

#include "allegroClass.h"
#include "Page.h"
#include "Image.h"
#include "ENCD_FILE.h"
#include "ENCDPage.h"
enum class menuState { MAINMENU, ENCODER, DECODER, ENCODING, DECODING, SUCCESS, ERROR, QUIT };

class Drawer {
public:
	Drawer() {}
	~Drawer() {}
	void drawMenu();
	void drawEncoder(std::vector<Page*>* pages);
	void drawDecoder(std::vector<ENCDPage*>* pages);
	void drawError();
	void drawSuccess();
	void getDrawTool(allegro_c* altool_) { this->altool = altool_; }

private:

	allegro_c * altool;

	void drawButton(int x, int y, std::string msg);
	void drawButton(int x, int y, int sizex, int sizey, bool selected, std::string msg);
	void drawMosaic(int pos, Image* img);
	void drawMosaic(int pos, ENCD_FILE * img);

	const int width = 300;
	const int height = 150;
	const int lineThickness = 4;
	const unsigned photo_w = SCREEN_W / 7 + 3;
	const unsigned photo_h = SCREEN_H / 7 + 3;

	const unsigned pos1_w = SCREEN_W / 7;
	const unsigned pos1_h = SCREEN_H / 7;
	const unsigned pos2_w = 3 * SCREEN_W / 7;
	const unsigned pos2_h = SCREEN_H / 7;
	const unsigned pos3_w = 5 * SCREEN_W / 7;
	const unsigned pos3_h = SCREEN_H / 7;
	const unsigned pos4_w = SCREEN_W / 7;
	const unsigned pos4_h = 3 * SCREEN_H / 7;
	const unsigned pos5_w = 3 * SCREEN_W / 7;
	const unsigned pos5_h = 3 * SCREEN_H / 7;
	const unsigned pos6_w = 5 * SCREEN_W / 7;
	const unsigned pos6_h = 3 * SCREEN_H / 7;
	const unsigned pos7_w = SCREEN_W / 7;
	const unsigned pos7_h = 5 * SCREEN_H / 7;
	const unsigned pos8_w = 3 * SCREEN_W / 7;
	const unsigned pos8_h = 5 * SCREEN_H / 7;
	const unsigned pos9_w = 5 * SCREEN_W / 7;
	const unsigned pos9_h = 5 * SCREEN_H / 7;
};