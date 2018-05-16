#include "ENCD_FILE.h"

using namespace boost::filesystem;

ENCD_FILE::ENCD_FILE(std::string path_)
{
	this->Path = path_;
	setName();
	setText();
}


ENCD_FILE::~ENCD_FILE()
{
}

void ENCD_FILE::toggleSelection(toggleVal select)
{
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

bool ENCD_FILE::getSelectValue()
{
	return selected;
}

void ENCD_FILE::setName()
{
	path p(Path.c_str());
	if (exists(p))	//me fijo si existe el path capaz se podria sacar
	{
		name = (p.string()); //esto devuelve el path donde se encuentra el archivo y el nombre de este
	}
}

void ENCD_FILE::setText()
{
	
}


std::string ENCD_FILE::getName() { 
	return this->name; 
}