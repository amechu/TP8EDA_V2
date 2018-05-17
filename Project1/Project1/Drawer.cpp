#include "Drawer.h"


/*No tendrá verificación, ya que solo habrá un observador y se llamará
cuando haya que dibujar*/

#define SIZEX 250
#define SIZEY 100

void Drawer::drawMenu() {

	al_clear_to_color(al_map_rgb(170, 160, 57));
	al_draw_text(altool->bigfont, al_map_rgb(196, 100, 2), SCREEN_W / 2, SCREEN_H / 8 - altool->fontSizeBig / 2, ALLEGRO_ALIGN_CENTER, "Welcome to Gary's Image Compressor");
	drawButton(1 * SCREEN_W / 4 - width / 2, 2 * SCREEN_H / 6, "[E]ncoding Menu");
	drawButton(3 * SCREEN_W / 4 - width / 2, 2 * SCREEN_H / 6, "[D]ecoding Menu");
	drawButton(SCREEN_W / 2 - width / 2, 4 * SCREEN_H / 6, "[Q]uit");
	al_flip_display();
}

void Drawer::drawEncoder(std::vector<Page*>* pages) {
	
	bool atLeastOneImg = false;
	bool foundPage = false;
	unsigned counter = 1;

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(altool->bigfont, al_map_rgb(196, 100, 2), SCREEN_W / 2, 25, ALLEGRO_ALIGN_CENTER, "Which images do you want Gary to encode?");

	for (Page* page : *pages) {
		if (page->isSelected() && !foundPage) {
			foundPage = true;
			al_draw_text(altool->bigfont, al_color_name("orange"), SCREEN_W / 2, SCREEN_H - 50, NULL, (std::to_string(page->getPageNumber())).c_str());
			for (Image* img : page->images) {
				if ((counter < 10) && (img != NULL)) {
					drawMosaic(counter, img);
					counter++;
					atLeastOneImg = true;
				}
			}
		}
	}

	if (!atLeastOneImg) {
		al_draw_text(altool->bigfont, al_map_rgb(196, 100, 2), SCREEN_W / 2, SCREEN_H / 2 - altool->fontSizeBig / 2, ALLEGRO_ALIGN_CENTER, "NO IMAGES FOUND. SAD!");
	}
	al_flip_display();
}

void Drawer::drawDecoder(std::vector<ENCDPage*>* pages) {
	
	bool atLeastOneImg = false;
	bool foundPage = false;
	unsigned counter = 1;


	ENCD_FILE * encdfile = NULL;


	al_clear_to_color(al_map_rgb(170, 160, 57));
	al_draw_text(altool->bigfont, al_map_rgb(196, 100, 2), SCREEN_W / 2, 25, ALLEGRO_ALIGN_CENTER, "Which images do you want Gary to decode?");

	for (ENCDPage* encdPage : *pages) {
		if (encdPage->isSelected() && !foundPage) {
			al_draw_text(altool->bigfont, al_color_name("orange"), SCREEN_W / 2, SCREEN_H - 50, NULL, (std::to_string(encdPage->getPageNumber())).c_str());
			foundPage = true;
			for (ENCD_FILE * encdfile : encdPage->encdfiles) {
				if ((counter < 10) && (encdfile != NULL)){
					drawMosaic(counter, encdfile);
					counter++;
					atLeastOneImg = true;
				}
			}
		}
	}

	if (!atLeastOneImg) {
		al_draw_text(altool->bigfont, al_map_rgb(196, 100, 2), SCREEN_W / 2, SCREEN_H / 2 - altool->fontSizeBig / 2, ALLEGRO_ALIGN_CENTER, "NO COMPRESSED IMAGES FOUND. SAD!");
	}

	al_flip_display();
}

void Drawer::drawError() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(altool->bigfont, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "ERROR! SAD.");
	al_draw_text(altool->bigfont, al_color_name("orange"), SCREEN_W / 2, SCREEN_H / 2 + 150, ALLEGRO_ALIGN_CENTER, "Quiting in 3..");
	al_flip_display();
	al_rest(1);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(altool->bigfont, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "ERROR! SAD.");
	al_draw_text(altool->bigfont, al_color_name("orange"), SCREEN_W / 2, SCREEN_H / 2 + 150, ALLEGRO_ALIGN_CENTER, "Quiting in 2..");
	al_flip_display();
	al_rest(1);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(altool->bigfont, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "ERROR! SAD.");
	al_draw_text(altool->bigfont, al_color_name("orange"), SCREEN_W / 2, SCREEN_H / 2 + 150, ALLEGRO_ALIGN_CENTER, "Quiting in 1..");
	al_flip_display();
	al_rest(1);
}

void Drawer::drawSuccess() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(altool->bigfont, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "SUCCESS!");
	al_draw_text(altool->bigfont, al_color_name("orange"), SCREEN_W / 2, SCREEN_H / 2 + 150, ALLEGRO_ALIGN_CENTER, "Quiting in 3..");
	al_flip_display();
	al_rest(1);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(altool->bigfont, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "SUCCESS!");
	al_draw_text(altool->bigfont, al_color_name("orange"), SCREEN_W / 2, SCREEN_H / 2 + 150, ALLEGRO_ALIGN_CENTER, "Quiting in 2..");
	al_flip_display();
	al_rest(1);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(altool->bigfont, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "SUCCESS!");
	al_draw_text(altool->bigfont, al_color_name("orange"), SCREEN_W / 2, SCREEN_H / 2 + 150, ALLEGRO_ALIGN_CENTER, "Quiting in 1..");
	al_flip_display();
	al_rest(1);
}

void Drawer::drawButton(int x, int y, std::string msg) {

	ALLEGRO_BITMAP* disp = al_get_target_bitmap();
	ALLEGRO_BITMAP* bitmap = al_create_bitmap(width, height);

	al_set_target_bitmap(bitmap);
	al_clear_to_color(al_map_rgb(250, 160, 57));
	al_draw_rectangle(2, 2, width - 2, height - 2, al_map_rgb(196, 100, 2), lineThickness);
	al_draw_text(altool->bigfont, al_map_rgb(196, 100, 2), width / 2, height / 2 + altool->fontSizeBig + 15, ALLEGRO_ALIGN_CENTRE, msg.c_str());
	al_set_target_bitmap(disp);
	al_draw_bitmap(bitmap, x, y, NULL);
}

void Drawer::drawButton(int x, int y, int sizex, int sizey, bool selected, std::string msg) {

	ALLEGRO_BITMAP* disp = al_get_target_bitmap();
	ALLEGRO_BITMAP* bitmap = al_create_bitmap(sizex, sizey);

	ALLEGRO_COLOR backcolor = al_map_rgb(250, 160, 57); //Si no esta seleccionado, el recuadro sera de este color.
	ALLEGRO_COLOR linecolor = al_map_rgb(196, 100, 2); //Si no esta seleccionado, el recuadro sera de este color.

	if (selected) {
		backcolor = al_map_rgb(0, 255, 0); //Si esta seleccionado, el recuadro es verde.
		linecolor = al_map_rgb(0, 150, 0);
	}

	al_set_target_bitmap(bitmap);
	al_clear_to_color(backcolor);
	al_draw_rectangle(2, 2, sizex - 2, sizey - 2, linecolor, lineThickness);
	al_draw_text(altool->smallfont, al_map_rgb(196, 100, 2), sizex / 2, sizey / 2 + altool->fontSizeSmall + 7, ALLEGRO_ALIGN_CENTRE, msg.c_str());
	al_set_target_bitmap(disp);
	al_draw_bitmap(bitmap, x - (sizex/2), y, NULL);
}

void Drawer::drawMosaic(int pos, Image* img) {

	if (img != NULL) {
		switch (pos) {
		case 1:
			if (img->getSelectValue())
				al_draw_tinted_scaled_bitmap(img->bitmap, al_color_name("red"), 0, 0, img->getWidth(), img->getHeight(), pos1_w, pos1_h, photo_w, photo_h, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos1_w, pos1_h, photo_w, photo_h, NULL);
			break;
		case 2:
			if (img->getSelectValue())
				al_draw_tinted_scaled_bitmap(img->bitmap, al_color_name("red"), 0, 0, img->getWidth(), img->getHeight(), pos2_w, pos2_h, photo_w, photo_h, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos2_w, pos2_h, photo_w, photo_h, NULL);
			break;
		case 3:
			if (img->getSelectValue())
				al_draw_tinted_scaled_bitmap(img->bitmap, al_color_name("red"), 0, 0, img->getWidth(), img->getHeight(), pos3_w, pos3_h, photo_w, photo_h, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos3_w, pos3_h, photo_w, photo_h, NULL);
			break;
		case 4:
			if (img->getSelectValue())
				al_draw_tinted_scaled_bitmap(img->bitmap, al_color_name("red"), 0, 0, img->getWidth(), img->getHeight(), pos4_w, pos4_h, photo_w, photo_h, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos4_w, pos4_h, photo_w, photo_h, NULL);
			break;
		case 5:
			if (img->getSelectValue())
				al_draw_tinted_scaled_bitmap(img->bitmap, al_color_name("red"), 0, 0, img->getWidth(), img->getHeight(), pos5_w, pos5_h, photo_w, photo_h, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos5_w, pos5_h, photo_w, photo_h, NULL);
			break;
		case 6:
			if (img->getSelectValue())
				al_draw_tinted_scaled_bitmap(img->bitmap, al_color_name("red"), 0, 0, img->getWidth(), img->getHeight(), pos6_w, pos6_h, photo_w, photo_h, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos6_w, pos6_h, photo_w, photo_h, NULL);
			break;
		case 7:
			if (img->getSelectValue())
				al_draw_tinted_scaled_bitmap(img->bitmap, al_color_name("red"), 0, 0, img->getWidth(), img->getHeight(), pos7_w, pos7_h, photo_w, photo_h, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos7_w, pos7_h, photo_w, photo_h, NULL);
			break;
		case 8:
			if (img->getSelectValue())
				al_draw_tinted_scaled_bitmap(img->bitmap, al_color_name("red"), 0, 0, img->getWidth(), img->getHeight(), pos8_w, pos8_h, photo_w, photo_h, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos8_w, pos8_h, photo_w, photo_h, NULL);
			break;
		case 9:
			if (img->getSelectValue())
				al_draw_tinted_scaled_bitmap(img->bitmap, al_color_name("red"), 0, 0, img->getWidth(), img->getHeight(), pos9_w, pos9_h, photo_w, photo_h, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos9_w, pos9_h, photo_w, photo_h, NULL);
			break;
		}
	}


}

void Drawer::drawMosaic(int pos, ENCD_FILE * img) {
	
	switch (pos) {
	case 1:
		drawButton(1 * SCREEN_W / 4, 2 * SCREEN_H / 9, SIZEX, SIZEY, img->getSelectValue(), img->getName());
			break;
	case 2:
		drawButton(2 * SCREEN_W / 4, 2 * SCREEN_H / 9, SIZEX, SIZEY, img->getSelectValue(), img->getName());
			break;
	case 3:
		drawButton(3 * SCREEN_W / 4, 2 * SCREEN_H / 9, SIZEX, SIZEY, img->getSelectValue(), img->getName());
			break;
	case 4:
		drawButton(1 * SCREEN_W / 4, 4 * SCREEN_H / 9, SIZEX, SIZEY, img->getSelectValue(), img->getName());
			break;
	case 5:
		drawButton(2 * SCREEN_W / 4, 4 * SCREEN_H / 9, SIZEX, SIZEY, img->getSelectValue(), img->getName());
			break;
	case 6:
		drawButton(3 * SCREEN_W / 4, 4 * SCREEN_H / 9, SIZEX, SIZEY, img->getSelectValue(), img->getName());
			break;
	case 7:
		drawButton(1 * SCREEN_W / 4, 6 * SCREEN_H / 9, SIZEX, SIZEY, img->getSelectValue(), img->getName());
			break;
	case 8:
		drawButton(2 * SCREEN_W / 4, 6 * SCREEN_H / 9, SIZEX, SIZEY, img->getSelectValue(), img->getName());
			break;
	case 9:
		drawButton(3 * SCREEN_W / 4, 6 * SCREEN_H / 9, SIZEX, SIZEY, img->getSelectValue(), img->getName());
			break;
	}
}

void Drawer::loadingScreen() {

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(altool->bigfont, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "LOADING.. PLEASE WAIT.");
	al_flip_display();
}

void Drawer::loadingScreenEncoding(std::string img)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(altool->bigfont, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "LOADING.. PLEASE WAIT.");
	al_draw_text(altool->bigfont, al_color_name("orange"), SCREEN_W / 2, SCREEN_H / 2 + 150, ALLEGRO_ALIGN_CENTER, ("Compressing image: " + img).c_str());
	al_flip_display();
}

void Drawer::loadingScreenDecoding(std::string file)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(altool->bigfont, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "LOADING.. PLEASE WAIT.");
	al_draw_text(altool->bigfont, al_color_name("orange"), SCREEN_W / 2, SCREEN_H / 2 + 150, ALLEGRO_ALIGN_CENTER, ("Decompressing file: " + file).c_str());
	al_flip_display();
}

void Drawer::loadingScreenPRE()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(altool->bigfont, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "LOADING.. PLEASE WAIT.");
	al_draw_text(altool->bigfont, al_color_name("orange"), SCREEN_W / 2, SCREEN_H / 2 + 150, ALLEGRO_ALIGN_CENTER, "Preparing images..");
	al_flip_display();
}

void Drawer::drawQUIT()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(altool->bigfont, al_color_name("orange"), SCREEN_W / 2, SCREEN_H / 2 + 150, ALLEGRO_ALIGN_CENTER, "Quiting in 3..");
	al_flip_display();
	al_rest(1);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(altool->bigfont, al_color_name("orange"), SCREEN_W / 2, SCREEN_H / 2 + 150, ALLEGRO_ALIGN_CENTER, "Quiting in 2..");
	al_flip_display();
	al_rest(1);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(altool->bigfont, al_color_name("orange"), SCREEN_W / 2, SCREEN_H / 2 + 150, ALLEGRO_ALIGN_CENTER, "Quiting in 1..");
	al_flip_display();
	al_rest(1);
}
