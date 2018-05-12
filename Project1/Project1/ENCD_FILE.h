#pragma once

#include <string>
#include "boost\filesystem.hpp"

class ENCD_FILE
{
public:
	ENCD_FILE();
	~ENCD_FILE();

private:
	std::string text; //Texto dentro del archivo

	std::string Path; //filepath del archivo con mayuscula sino hace conflicto con path de filesystem

	std::string name; //nombre del archivo
	
	bool selected; //Si esta seleccionada

	bool error; //Si hubo error con el archivo
	
	void setName(); //A partir del path, busco el nombre del archivo y lo pongo en name
	
	void setText(); //A partir del path, busco el contenido del archivo
};

