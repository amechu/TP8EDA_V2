#pragma once
#include "allegro5\allegro.h"
#include "boost\filesystem.hpp"
#include "lodepng.h"
#include <string>
#include <vector>

class Image
{
public:
	Image(std::string path_);
	~Image();

private:
	
	ALLEGRO_BITMAP * bitmap; //Bitmap de allegro
	
	std::vector<unsigned char> pixels; //Vector de pixeles de la imagen
	
	std::string path; //Filepath al archivo
	
	std::string name; //Nombre de la imagen
	
	unsigned width; //Ancho de la imagen
	
	unsigned height; //Alto de la imagen

	bool selected = false; //Si el usuario la ha seleccionado o no

	bool error = false; //Si hubo error con la imagen

	void setName(); /*Utiliza el path del archivo para colocarle un nombre a la foto*/

	void loadBitmap(); /*Carga el bitmap con allegro, utiliza el path*/

	void destroyBitmap(); /*Destruye el bitmap con allegro, utiliza el path*/

	void decodeImage(); /*Pasandole a la funcion decode de lodepng el vector de pixeles "pixels",
	el ancho "width", el alto "height" y el filepath "path" a la imagen, te devuelve el ancho, el alto de la imagen
	y el vector de pixeles lleno.*/
};

