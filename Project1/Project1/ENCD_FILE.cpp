#include "ENCD_FILE.h"

using namespace boost::filesystem;

ENCD_FILE::ENCD_FILE()
{
}


ENCD_FILE::~ENCD_FILE()
{
}

void ENCD_FILE::setName()
{
	path p(Path.c_str());
	if (exists(p))	//me fijo si existe el path capaz se podria sacar
	{
		name = (p.filename().string()); //esto deberia devolver el name del archivo como un string
	}
}

void ENCD_FILE::setText()
{
	//magia de ari
}
