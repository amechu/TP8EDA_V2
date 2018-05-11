#pragma once
#include "Image.h"
#include <boost\filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>

using namespace boost::filesystem;

using namespace std;
class FileReader
{
public:
	FileReader();
	~FileReader();

	bool load(string);

	


private:
	
};

