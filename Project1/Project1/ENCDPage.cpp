#include "ENCDPage.h"

void ENCDPage::addENCD(std::string path_)
{
	if (encdfiles.size() <= encdfiles.max_size() - 1) {
		encdfiles[encdfiles.size()] = new ENCD_FILE(path_);
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
