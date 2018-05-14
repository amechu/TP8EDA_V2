#include "allegroClass.h"
#include <iostream>


allegro_c::allegro_c() {

	bool check1 = false;
	bool check2 = false;

	if (al_init())
	{
		if (al_install_audio())
		{
			if (al_init_acodec_addon())
			{
				if ((al_reserve_samples(2)))
				{
					if (al_init_image_addon())
					{
						if (al_install_keyboard())
						{
							if ((ev_queue = al_create_event_queue()))
							{
								if (al_init_font_addon())
								{
									if ((display = al_create_display(SCREEN_W, SCREEN_H)))
									{
										check1 = true;
										al_register_event_source(this->ev_queue, al_get_keyboard_event_source());
										al_register_event_source(this->ev_queue, al_get_display_event_source(this->display));
										al_set_window_title(display, "ENCD CODING HANDLER");
										ALLEGRO_BITMAP * icon = al_load_bitmap("icon.jpg");
										al_set_display_icon(display, icon);
									}
								}
							}
						}
					}
					else
						std::cout << "ERROR: Failed to load Image addon" << std::endl;
				}
				else
					std::cout << "ERROR: Failed to reserve sample" << std::endl;
			}
			else
				std::cout << "ERROR: Failed to install acodec addon" << std::endl;
		}
		else
			std::cout << "ERROR: Failed to install audio" << std::endl;
	}
	else
		std::cout << "ERROR: Failed to initialize allegro system" << std::endl;

	if (check1) {
		if (al_init_ttf_addon()) {
			if (smallfont = al_load_font("montserrat.ttf", fontSizeSmall, NULL)) {
				if (bigfont = al_load_font("montserrat.ttf", fontSizeBig, NULL)) {
					if (al_init_primitives_addon()) {
						check2 = true;
					}
					else
						std::cout << "ERROR: Failed to install primitives" << std::endl;
				}
				else
					std::cout << "ERROR: Failed to install font" << std::endl;
			}
			else
				std::cout << "ERROR: Failed to install font" << std::endl;
		}
		else
			std::cout << "ERROR: Failed to install ttf addon" << std::endl;
	}

	initgood = (check1 && check2);
}

allegro_c::~allegro_c()
{
	al_destroy_display(display);
	al_stop_samples();
	al_destroy_sample(music[0]);
	al_destroy_sample(music[1]);
	al_destroy_event_queue(ev_queue);
	al_shutdown_image_addon();
	al_uninstall_audio();
}

bool allegro_c::load_music(const char * music_file, unsigned char i) //Devuelve 1 si todo salio bien
{
	bool result;
	if ((i < SONGSQTY) && (this->music[i] = al_load_sample(music_file))) {
		result = true;
	}
	else {
		std::cout << "ERROR: Failed to find music file." << std::endl;
		result = false;
	}

	return result;

}

void allegro_c::updateDisplay()
{
	al_flip_display();
}

ALLEGRO_EVENT_QUEUE * allegro_c::getEventQueue()
{
	return ev_queue;
}

void allegro_c::play_music(unsigned char i)
{
	if(i == 0)
		al_play_sample(this->music[0], 1.0, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	else if(i == 1)
		al_play_sample(this->music[1], 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void allegro_c::start_timer() {
	al_start_timer(this->timer);
}