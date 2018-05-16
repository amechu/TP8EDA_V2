#pragma once

#include <string>

enum { ERROR1 = -1, ERROR2 = -2, ERROR3 = -3 };
const unsigned int NPARAMETERS = 1;
const unsigned int NKEYS = 2;
const unsigned int NVALUES = 1;

const unsigned int MAXTHRESHOLD = 765;
const unsigned int DEFAULTH = 20;

typedef struct
{
	char*  parameters[NPARAMETERS];
	char*  key[NKEYS];
	char*  value[NVALUES];

}parseData;

class Parser
{
public:
	Parser() { parseData.key[0] = (char*) "PATH"; parseData.key[1] = (char*) "THRESHOLD";
	};
	~Parser();

	int Read(int argc, char *argv[]);

	std::string getPath() { return path; }
	unsigned getThreshold() { return threshold; }

private:
	void Do(char *key, char *value);
	parseData parseData;
	std::string path;
	unsigned threshold;
};

