#pragma once

#include <string>
#include <array>
#include "ENCD_FILE.h"

class ENCDPage
{
public:
public:
	ENCDPage(unsigned char pageNumber_) : pageNumber(pageNumber_) { if (pageNumber_ == 1) selected = true; }
	~ENCDPage() {}

	void addENCD(std::string path_);
	ENCD_FILE * getENCD(int i);

	bool const isSelected();
	void setSelected(bool set) { selected = set; }

	unsigned char getPageNumber() { return pageNumber; }

	std::array<ENCD_FILE*, 9> encdfiles = { NULL };

private:
	unsigned char pageNumber;
	bool selected = false;
	unsigned totalencd = 0;
};

