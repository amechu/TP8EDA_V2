#include "Page.h"

void Page::addImage(std::string path_) {
	if (images.size() <= images.max_size() - 1) {
		images[images.size()] = new Image(path_);
	 }
}

bool const Page::isSelected()
{
	return selected;
}

Image * Page::getImage(int i){ 

		return images[i - 1]; //i-1 para ser coherente con el input que sera de 1 a 9.
}
