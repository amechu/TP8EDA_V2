#include "FileReader.h"



FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}

bool FileReader::load(string dir)
{
	bool error=false;
	path p(dir);
	std::string auxString;
	std::string check = "";
	if (exists(p))
	{
		if (is_directory(p))     // is p a directory?
		{
			for (directory_iterator itr(p); itr != directory_iterator(); itr++)
			{


				if (is_regular_file(itr->path())) //me fijo si no hay otras carpetas por ahi en el directorio
				{
					(auxString = (itr->path().filename().string()));
					std::stringstream auxss(auxString);
					while (getline(auxss, check, '.'))
					{
						if (check == "\n")
						{
							break;
						}
						if (!strcmp(check.c_str(), "png"))	//poner para los ENCD
						{
							
							pngpaths.push_back(auxString);	//subo el path al vector
						}
						else if (!strcmp(check.c_str(), "ENCD"))
						{
							ENCDpaths.push_back(auxString);
							
						}
					}
					;
				}


			}

		}
	}
	else
	{
		error=true;	//pq esto me va a decir despues si es un error o no
	}
	return error;
}
