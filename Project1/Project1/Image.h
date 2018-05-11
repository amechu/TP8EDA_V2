#pragma once
#include "allegro5\allegro.h"
#include <string>

class Image
{
public:
	Image(std::string path_, unsigned width_, unsigned height_);
	~Image();
private:
	ALLEGRO_BITMAP * bitmap;
	std::string path;
	unsigned width;
	unsigned height;
	bool selected;
	std::string name;
	void setName();
	void loadBitmap();
	void destroyBitmap();
};

