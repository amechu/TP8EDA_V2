#include "Image.h"

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
	/*hace tu magia ariel*/
}

void Image::loadBitmap()
{
}

void Image::destroyBitmap()
{
	
}

void Image::decodeImage()
{
	unsigned err = lodepng::decode(this->pixels, this->width, this->height, this->path);

	if (err)
		this->error = true;
}
