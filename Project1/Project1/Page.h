#pragma once

#include "Image.h"
#include <array>
#include <string>

class Page
{
public:
	Page(unsigned char pageNumber_) : pageNumber(pageNumber_) {};
	~Page() { for (Image* img : images) { delete img; } };
	void addImage (std::string path_, unsigned width, unsigned height);
	bool const isSelected();

private:
	std::array<Image*, 9> images;
	unsigned char pageNumber;
	bool selected;
};

