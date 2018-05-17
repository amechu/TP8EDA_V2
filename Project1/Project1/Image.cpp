#include "Image.h"

using namespace boost::filesystem;

Image::Image(std::string path_)
{
	this->Path = path_;
	setName(); //con el path, encuentra el nombre del archivo y lo carga a "name".
	decodeImage();
	loadBitmap(); //con el path, carga el bitmap de allegro.
}

Image::~Image()
{
	destroyBitmap();
}

void Image::setName()
{
	path p(Path);

	if (exists(p))
	{
		name = (p.filename().string()); //esto deberia devolver el name del archivo como un string
	}
}

void Image::loadBitmap()
{
	this->bitmap = al_load_bitmap(((this->Path).c_str()));
}

void Image::destroyBitmap()
{
	al_destroy_bitmap(this->bitmap);
}

void Image::decodeImage()
{
	unsigned err = lodepng::decode(this->pixels, this->width, this->height, this->Path);

	if (err)
		this->error = true;
	
}

void Image::prepareImage()
{
	unsigned auxwidth, auxheight, side;

	auxwidth = pow(2, ceil(log(width) / log(2))); //Me da el numero mas cercano potencia de 2 para arriba
	auxheight = pow(2, ceil(log(height) / log(2)));
	if (auxwidth >= auxheight) {
		side = auxwidth;
	}
	else {
		side = auxheight;
	}
	for (int i = 0; i < (pow(side, 2) - (width*height)); i++) {
		for (int j = 0; j < 4; j++) //Meto 4 FF por pixel (blancos)
			pixels.push_back(0xFF);
	}
	width = height = side;
}

void Image::toggleSelection(toggleVal select) {
	switch (select) {
	case toggleVal::TOGGLETRUE:
		this->selected = true;
		break;

	case toggleVal::TOGGLEFALSE:
		this->selected = false;
		break;

	case toggleVal::TOGGLE:
		if (this->selected == true)
			this->selected = false;
		else
			this->selected = true;
		break;

	}
}

unsigned Image::getWidth()
{
	return width;
}

unsigned Image::getHeight()
{
	return height;
}


std::string Image::getName() { 
	return this->name; 
}