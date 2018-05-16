#include "Image.h"

using namespace boost::filesystem;

Image::Image(std::string path_)
{
	this->Path = path_;
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
	unsigned auxwidth, auxheight, side;

	unsigned err = lodepng::decode(this->pixels, this->width, this->height, this->Path);

	if (err)
		this->error = true;
	else {
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
		if (((*pointer) <= (MAXRED)) && ((*pointer) > (MAXGREEN)))	//rojo
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