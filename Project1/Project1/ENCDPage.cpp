#include "ENCDPage.h"

void ENCDPage::addENCD(std::string path_)
{
	if (totalencd < 9) {
		ENCD_FILE* encdfile = new ENCD_FILE(path_);
		if (path_ == "") {
			encdfiles[totalencd] = NULL;
		}
		else {
			encdfiles[totalencd] = encdfile;
		}
		totalencd++;
	}
}

ENCD_FILE * ENCDPage::getENCD(int i)
{
	return encdfiles[i-1];
}

bool const ENCDPage::isSelected()
{
	return selected;
}
