#include "Image.h"

Image::Image(std::string path_, unsigned width_, unsigned height_) : path(path_), width(width_), height(height_)
{
	setName();
	loadBitmap();
}

Image::~Image()
{
	destroyBitmap();
}

void Image::setName()
{
}

void Image::loadBitmap()
{
}

void Image::destroyBitmap()
{
}
