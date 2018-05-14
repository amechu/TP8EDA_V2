#include "Drawer.h"


	/*No tendrá verificación, ya que solo habrá un observador y se llamará
	cuando haya que dibujar*/

void Drawer::drawMenu() {
	
	al_clear_to_color(al_map_rgb(170, 160, 57));
	al_draw_text(altool->bigfont, al_map_rgb(196, 100, 2), SCREEN_W / 2, SCREEN_H / 8 - altool->fontSizeBig/2, ALLEGRO_ALIGN_CENTER, "Welcome to Gary's Image Compressor");
	drawButton(1*SCREEN_W / 4 - width/2, 2*SCREEN_H / 6, "[E]ncoding Menu");
	drawButton(3 * SCREEN_W / 4 - width/2, 2*SCREEN_H / 6, "[D]ecoding Menu");
	drawButton(SCREEN_W / 2 - width/2, 4 * SCREEN_H / 6, "[Q]uit");
	al_flip_display();
}

void Drawer::drawEncoder(std::vector<Page>* pages) {
	
	bool foundPage = false;
	unsigned counter = 1;

	al_clear_to_color(al_map_rgb(0,0,0));
	for (Page page : *pages) {
		if (page.isSelected() && !foundPage) {
			foundPage = true;
			for (Image* img : page.images) {
				if (counter < 10) {
					drawMosaic(counter, img);
					counter++;
				}
			}
		}
	}
	al_flip_display();
}

void Drawer::drawDecoder(std::vector<Page>* pages){}

void Drawer::drawError(){}

void Drawer::drawSuccess(){}

void Drawer::drawButton(int x, int y, std::string msg){

	ALLEGRO_BITMAP* disp = al_get_target_bitmap();
	ALLEGRO_BITMAP* bitmap = al_create_bitmap(width, height);
	
	al_set_target_bitmap(bitmap);
	al_clear_to_color(al_map_rgb(250, 160, 57));
	al_draw_rectangle(2, 2, width-2, height-2, al_map_rgb(196, 100, 2), lineThickness);
	al_draw_text(altool->bigfont, al_map_rgb(196, 100, 2), width/2 , height/2 + altool->fontSizeBig +15, ALLEGRO_ALIGN_CENTRE, msg.c_str());
	al_set_target_bitmap(disp);
	al_draw_bitmap(bitmap, x, y, NULL);
}

void Drawer::drawMosaic(int pos, Image* img) {

	switch (pos) {
	case 1:
		if(img->getSelectValue())
			al_draw_scaled_bitmap(img->bitmap, 0, 0, img->getWidth(), img->getHeight(), pos1_w - 10, pos1_h -10, photo_w + 20, photo_h + 20, NULL);
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

