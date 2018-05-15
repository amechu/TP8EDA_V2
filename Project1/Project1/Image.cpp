#include "Image.h"

using namespace boost::filesystem;

Image::Image(std::string path_)
{
	setName(); //con el path, encuentra el nombre del archivo y lo carga a "name".
	decodeImage(); //con el path, llena el vector pixels de pixeles y carga el ancho y alto de la imagen.
	loadBitmap(); //con el path, carga el bitmap de allegro.
	this->Path = path_;
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
	this->bitmap = al_load_bitmap((this->Path).c_str());
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

double Image::getTreshold(unsigned width, unsigned heigth, std::vector<unsigned char>&rawpixels)
{
	uint32_t * pointer;
	pointer = (uint32_t*)(&(rawpixels[0]));

	uint32_t maxred = MAXGREEN;
	uint32_t minred = MAXRED;	//PONGO EL MAXIMO COLOR POSIBLE EN EL MINIMO PARA QUE SE VAYA RENOVANDO

	uint32_t maxgreen = MAXBLUE;
	uint32_t mingreen = MAXGREEN;

	uint32_t maxblue = 0;
	uint32_t minblue = MAXBLUE;

	for (int i = 0; i < (width*heigth); i++)	//con las iteraciones me fijo cual es el max y min de cada color
	{
		if (((*pointer) <= (MAXRED)) && ((*pointer) >(MAXGREEN)))	//rojo
		{
			if ((*pointer) > maxred)
			{
				maxred = (*pointer);	//pongo el contenido del puntero en maximo rojo
			}
			else if ((*pointer) < minred)
			{
				minred = (*pointer);
			}
		}
		else if (((*pointer) <= (MAXGREEN)) && ((*pointer) > (MAXBLUE))) //verde
		{
			if ((*pointer) > maxgreen)
			{
				maxgreen = (*pointer);
			}
			else if ((*pointer) < mingreen)
			{
				mingreen = (*pointer);
			}
		}
		else if (((*pointer) <= (MAXBLUE)) && ((*pointer) >= 0)) //azul
		{
			if ((*pointer) > maxblue)
			{
				maxblue = (*pointer);
			}
			else if ((*pointer) < minblue)
			{
				minblue = (*pointer);
			}
		}
		pointer++;	//cambiar todo pq es un cancer algo asi es la idea pero mejor hacerla que se mueva char a char
	}

	return (maxred - minred + maxblue - minblue + maxgreen - mingreen);
}