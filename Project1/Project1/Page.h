#pragma once

#include "Image.h"
#include <array>
#include <string>



class Page
{
public:
	Page(unsigned char pageNumber_) : pageNumber(pageNumber_) {};
	~Page() { for (Image* img : images) { delete img; } };

	void addImage (std::string path_);
	Image * getImage(int i);

	bool const isSelected();

	unsigned char getPageNumber() { return pageNumber; }

	std::array<Image*, 9> images = { NULL };

private:
	unsigned char pageNumber;
	bool selected;
	unsigned totalimages = 0;
};

