#include "Page.h"
#include "Parser.h"
#include <iostream>

int main(int argc, char*argv[]) {

	Parser parser;

	if (!parser.Read(argc, argv)){

	}
	else {
		std::cout << "Parser error. Please check your input. This program takes a path and a threshold." << std::endl;
		std::cout << "Correct format: ' -path [Path] -threshold [0 -" << MAXTHRESHOLD <<"] '" << std::endl;
		std::cout << "Press any key to end the program and try again." << std::endl;
		getchar();
	}

	return 0;
}