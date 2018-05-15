#include "Page.h"

void Page::addImage(std::string path_) {
	if (totalimages < 9) {
		Image* img = new Image(path_);
		if (path_ == "") {
			images[this->totalimages] = NULL;
		}
		else {
			images[this->totalimages] = img;
		}
		totalimages++;
	}
}

bool const Page::isSelected()
{
	return selected;
}

Image * Page::getImage(int i){ 

		return images[i - 1]; //i-1 para ser coherente con el input que sera de 1 a 9.
}
