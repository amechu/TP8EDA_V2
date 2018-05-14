#pragma once

#include <iostream>
#include <allegro5/allegro5.h> 
#include <allegro5/allegro_color.h> 
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5\allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define BACKGROUNDMUSIC "background.wav"
#define WRONGINPUTSFX "wrong.wav"
#define WRONG 1
#define SCREEN_W 1000
#define SCREEN_H 600

#define SONGSQTY 2

class allegro_c {

public:

	allegro_c();
	~allegro_c();
	ALLEGRO_EVENT_QUEUE * getEventQueue();
	bool load_music(const char * music_file, unsigned char i);
	void play_music(unsigned char i);
	void updateDisplay();
	void start_timer();
	int fontSizeSmall = -15;
	int fontSizeBig = -35;
	ALLEGRO_FONT* smallfont;
	ALLEGRO_FONT* bigfont;
	bool initgood;

private:

	ALLEGRO_DISPLAY * display = NULL;
	ALLEGRO_EVENT_QUEUE * ev_queue = NULL;
	ALLEGRO_SAMPLE * music[SONGSQTY] = { NULL };
	ALLEGRO_TIMER * timer = NULL;
};
