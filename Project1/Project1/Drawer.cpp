#include "Drawer.h"


/*No tendr� verificaci�n, ya que solo habr� un observador y se llamar�
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

void Drawer::drawEncoder(std::vector<Page>* pages) {

	bool atLeastOneImg = false;
	bool foundPage = false;
	unsigned counter = 1;

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(altool->bigfont, al_map_rgb(196, 100, 2), SCREEN_W / 2, SCREEN_H / 9 - altool->fontSizeBig / 2, ALLEGRO_ALIGN_CENTER, "Which images do you want Gary to encode?");

	for (Page page : *pages) {
		if (page.isSelected() && !foundPage) {
			foundPage = true;
			for (Image* img : page.images) {
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

void Drawer::drawDecoder(std::vector<ENCDPage>* pages) {
	
	bool atLeastOneImg = false;
	bool foundPage = false;
	unsigned counter = 1;


	ENCD_FILE * encdfile = NULL;


	al_clear_to_color(al_map_rgb(170, 160, 57));
	al_draw_text(altool->bigfont, al_map_rgb(196, 100, 2), SCREEN_W / 2, SCREEN_H / 9 - altool->fontSizeBig / 2, ALLEGRO_ALIGN_CENTER, "Which images do you want Gary to decode?");

	for (ENCDPage encdPage : *pages) {
		if (encdPage.isSelected() && !foundPage) {
			foundPage = true;
			for (ENCD_FILE * encdfile : encdPage.encdfiles) {
				if ((counter < 10) && (encdfile != NULL)){
					drawMosaic(counter, encdfile);
					counter++;
					atLeastOneImg = true;
				}
			}
		}
	}

	//for (int i = 0; i < 10; i++) {
	//	if (counter < 10) {
	//		drawMosaic(counter, encdfile);
	//		counter++;
	//	}
	//}


	if (!atLeastOneImg) {
		al_draw_text(altool->bigfont, al_map_rgb(196, 100, 2), SCREEN_W / 2, SCREEN_H / 2 - altool->fontSizeBig / 2, ALLEGRO_ALIGN_CENTER, "NO IMAGES FOUND. SAD!");
	}

	al_flip_display();
}

void Drawer::drawError() {}

void Drawer::drawSuccess() {}

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
	al_draw_text(altool->bigfont, al_map_rgb(196, 100, 2), sizex / 2, sizey / 2 + altool->fontSizeBig + 15, ALLEGRO_ALIGN_CENTRE, msg.c_str());
	al_set_target_bitmap(disp);
	al_draw_bitmap(bitmap, x - (sizex/2), y, NULL);
}

void Drawer::drawMosaic(int pos, Image* img) {

	if (img != NULL) {
		switch (pos) {
		case 1:
			if (img->getSelectValue())
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos1_w - 10, pos1_h - 10, photo_w + 20, photo_h + 20, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos1_w, pos1_h, photo_w, photo_h, NULL);
			break;
		case 2:
			if (img->getSelectValue())
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos2_w - 10, pos1_h - 10, photo_w + 20, photo_h + 20, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos2_w, pos1_h, photo_w, photo_h, NULL);
			break;
		case 3:
			if (img->getSelectValue())
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos3_w - 10, pos1_h - 10, photo_w + 20, photo_h + 20, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos3_w, pos1_h, photo_w, photo_h, NULL);
			break;
		case 4:
			if (img->getSelectValue())
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos4_w - 10, pos1_h - 10, photo_w + 20, photo_h + 20, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos4_w, pos1_h, photo_w, photo_h, NULL);
			break;
		case 5:
			if (img->getSelectValue())
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos5_w - 10, pos1_h - 10, photo_w + 20, photo_h + 20, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos5_w, pos1_h, photo_w, photo_h, NULL);
			break;
		case 6:
			if (img->getSelectValue())
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos6_w - 10, pos1_h - 10, photo_w + 20, photo_h + 20, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos6_w, pos1_h, photo_w, photo_h, NULL);
			break;
		case 7:
			if (img->getSelectValue())
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos7_w - 10, pos1_h - 10, photo_w + 20, photo_h + 20, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos7_w, pos1_h, photo_w, photo_h, NULL);
			break;
		case 8:
			if (img->getSelectValue())
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos8_w - 10, pos1_h - 10, photo_w + 20, photo_h + 20, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos8_w, pos1_h, photo_w, photo_h, NULL);
			break;
		case 9:
			if (img->getSelectValue())
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos9_w - 10, pos1_h - 10, photo_w + 20, photo_h + 20, NULL);
			else
				al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos9_w, pos1_h, photo_w, photo_h, NULL);
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
		drawButton(1 * SCREEN_W / 4, 5 * SCREEN_H / 9, SIZEX, SIZEY, img->getSelectValue(), img->getName());
			break;
	case 5:
		drawButton(2 * SCREEN_W / 4, 5 * SCREEN_H / 9, SIZEX, SIZEY, img->getSelectValue(), img->getName());
			break;
	case 6:
		drawButton(3 * SCREEN_W / 4, 5 * SCREEN_H / 9, SIZEX, SIZEY, img->getSelectValue(), img->getName());
			break;
	case 7:
		drawButton(1 * SCREEN_W / 4, 7 * SCREEN_H / 9, SIZEX, SIZEY, img->getSelectValue(), img->getName());
			break;
	case 8:
		drawButton(2 * SCREEN_W / 4, 7 * SCREEN_H / 9, SIZEX, SIZEY, img->getSelectValue(), img->getName());
			break;
	case 9:
		drawButton(3 * SCREEN_W / 4, 7 * SCREEN_H / 9, SIZEX, SIZEY, img->getSelectValue(), img->getName());
			break;
	}

	//switch (pos) {
	//case 1:
	//	drawButton(1 * SCREEN_W / 4, 2 * SCREEN_H / 9, SIZEX, SIZEY, true, "TEST");
	//	break;
	//case 2:
	//	drawButton(2 * SCREEN_W / 4, 2 * SCREEN_H / 9, SIZEX, SIZEY, true, "TEST");
	//	break;
	//case 3:
	//	drawButton(3 * SCREEN_W / 4, 2 * SCREEN_H / 9, SIZEX, SIZEY, true, "TEST");
	//	break;
	//case 4:
	//	drawButton(1 * SCREEN_W / 4, 4 * SCREEN_H / 9, SIZEX, SIZEY, true, "TEST");
	//	break;
	//case 5:
	//	drawButton(2 * SCREEN_W / 4, 4 * SCREEN_H / 9, SIZEX, SIZEY, true, "TEST");
	//	break;
	//case 6:
	//	drawButton(3 * SCREEN_W / 4, 4 * SCREEN_H / 9, SIZEX, SIZEY, false, "TEST");
	//	break;
	//case 7:
	//	drawButton(1 * SCREEN_W / 4, 6* SCREEN_H / 9, SIZEX, SIZEY, false, "TEST");
	//	break;
	//case 8:
	//	drawButton(2 * SCREEN_W / 4, 6 * SCREEN_H / 9, SIZEX, SIZEY, false, "TEST");
	//	break;
	//case 9:
	//	drawButton(3 * SCREEN_W / 4, 6 * SCREEN_H / 9, SIZEX, SIZEY, false, "TEST");
	//	break;
	//}


}

