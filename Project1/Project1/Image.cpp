#include "Image.h"

using namespace boost::filesystem;

Image::Image(std::string path_)
{
	/*hace tu magia ariel*/
	setName(); //con el path, encuentra el nombre del archivo y lo carga a "name".
	decodeImage(); //con el path, llena el vector pixels de pixeles y carga el ancho y alto de la imagen.
	loadBitmap(); //con el path, carga el bitmap de allegro.
}

Image::~Image()
{
	destroyBitmap();
}

void Image::setName()
{	
	path p(Path.c_str());
	if (exists(p))
	{
		name = (p.filename().string()); //esto deberia devolver el name del archivo como un string
	}
}

void Image::loadBitmap()
{
}

void Image::destroyBitmap()
{
	
}

void Image::decodeImage()
{
	unsigned err = lodepng::decode(this->pixels, this->width, this->height, this->Path);

	if (err)
		this->error = true;
}

void Image::toggleSelection(toggleVal select){ 
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
