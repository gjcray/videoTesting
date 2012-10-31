/*
 * parse.h
 * parse the params into globals
 */

#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include "global.h"

class Parse_C {
public:
	inline Parse_C() {}
	inline ~Parse_C() {}
	/*
	 * parse the parameters from file into paramMap
	 */
	void Parse_Config_File(char *configFile);

	/*
	 * assign globals from paramMap
	 */
	bool Parse_Params(unsigned int paramNo, int &data);
private:
	std::vector<int> paramMap;
};

#endif

